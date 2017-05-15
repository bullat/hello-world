#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>
#include <set>

using namespace std;
double sq(double a) { return a*a;}

struct PC { double R, H; };
auto f1 = [](const PC& l, const PC& r)->bool
{
	if ( l.R > r.R )
		return true;
	else if ( l.R < r.R )
		return false;
	else // l.R == r.R
		return ( l.H > r.H );
};
auto f2 = []( const PC& l, const PC& r )->bool
{
	const double _l = l.R * l.H;
	const double _r = r.R * r.H;
	return _l > _r;
};

typedef multiset<PC,bool(*)(const PC&, const PC&)> multiset_PC;


int main()
{
	int Ntests;
	cin >> Ntests;

	for ( int Ntest = 0; Ntest < Ntests; ++Ntest )
	{
		int N, K;
		cin >> N >> K; // total num and ordered num
		multiset_PC cakes( f1 ); // sorted by raduis and then height
		for (int i=0; i<N; ++i )
		{
			PC tmp;
			cin >> tmp.R >> tmp.H;
			cakes.insert( tmp );
		}
		multiset_PC cakes2( cakes.cbegin(), cakes.cend(), f2 ); // sorted by side area

		double S = -10000000;
		multiset_PC::const_iterator b = cakes.cbegin();
		for ( int i = 0, i_end = N - K; i <= i_end; ++i, ++b )
		{
			_ASSERTE( b != cakes.cend() );
			const PC& cake = *b;
			cakes2.erase( cakes2.find( cake ) );
			if ( b != cakes.cbegin() )
			{
				multiset_PC::const_iterator prev = b;
				--prev;
				if ( cake.R == prev->R )
					continue;
			}

			double _s = sq( cake.R ) + 2*cake.R*cake.H;
			_ASSERTE( cakes2.size() >= K-1 );
			multiset_PC::const_iterator b2 = cakes2.cbegin();
			for ( int j = 0; j < K - 1; ++j )
			{
				_s += 2 * b2->R * b2->H;
				++b2;
			}
			if ( _s > S )
				S = _s;
		}
		S *= M_PI;

		cout << setprecision( 6 ) << fixed << "Case #" << Ntest+1 << ": " << S << endl;
	}

	return 0;
}
