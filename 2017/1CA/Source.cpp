#include <iostream>
#include <iomanip>
#include <set>
#include <tuple>

const double M_PI = 3.14159265358979323846;

struct Pancake
{
	double R, H;
	static bool compare_RH(const Pancake& l, const Pancake& r)
	{
		// for sort by raduis and then height
		return std::tie( l.R, l.H ) > std::tie( r.R, r.H );
	}
	static bool compare_SideArea(const Pancake& l, const Pancake& r)
	{
		// for sort by side area
		return l.R * l.H > r.R * r.H;
	}
	double getSideArea() const
	{
		return 2 * R * H;
	}
	double getBottomArea() const
	{
		return R * R;
	}
};
typedef std::multiset<Pancake,bool(*)(const Pancake&, const Pancake&)> multiset_PC;


int main()
{
	std::cout << std::setprecision( 6 ) << std::fixed;
	int Ntests;
	std::cin >> Ntests;

	for ( int Ntest = 0; Ntest < Ntests; ++Ntest )
	{
		int N, K;
		std::cin >> N >> K; // total num and ordered num of pancakes
		multiset_PC cakes_RH( Pancake::compare_RH );
		for (int i=0; i<N; ++i )
		{
			Pancake tmp;
			std::cin >> tmp.R >> tmp.H;
			cakes_RH.insert( tmp );
		}
		multiset_PC cakes_SideArea( cakes_RH.cbegin(), cakes_RH.cend(), Pancake::compare_SideArea );

		auto it_remove = cakes_RH.cend();
		_ASSERTE( cakes_RH.size() >= K-1 );
		std::advance( it_remove, 1-K ); // remove last K-1 elems
		cakes_RH.erase( it_remove, cakes_RH.cend() );

		double S = -DBL_MAX;
		for ( auto it = cakes_RH.cbegin(), it_end = cakes_RH.cend(); it != it_end; ++it )
		{
			const Pancake& cake = *it;
			cakes_SideArea.erase( cakes_SideArea.find( cake ) );
			if ( it != cakes_RH.cbegin() && cake.R == std::prev(it)->R )
					continue;

			double _s = cake.getBottomArea() + cake.getSideArea();
			_ASSERTE( cakes_SideArea.size() >= K-1 );
			auto it2_end = cakes_SideArea.cbegin();
			std::advance( it2_end, K-1 ); // create range for 'first K-1 elems'
			for ( auto it2 = cakes_SideArea.cbegin(); it2 != it2_end; ++it2 )
				_s += it2->getSideArea();
			if ( _s > S )
				S = _s;
		}

		std::cout << "Case #" << Ntest+1 << ": " << S * M_PI << std::endl;
	}

	return 0;
}
