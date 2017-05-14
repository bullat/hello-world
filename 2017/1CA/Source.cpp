#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
double sq(double a) { return a*a;}

int main()
{
	int Ntests;
	cin >> Ntests;

	for ( int Ntest = 0; Ntest < Ntests; ++Ntest )
	{
		int N, K;
		cin >> N >> K; // total num and ordered num
		struct PC { double R, H; };
		vector<PC> cakes( N );
		for (int i=0; i<N; ++i )
			cin >> cakes[i].R >> cakes[i].H;

		sort( cakes.begin(), cakes.end(),
			[](const PC& l, const PC& r)->bool
			{
				if ( l.R > r.R )
					return true;
				else if ( l.R < r.R )
					return false;
				else // l.R == r.R
					return ( l.H > r.H );
			}
		);

		double S = -10000000;
		for ( int i = 0, i_end = N - K; i <= i_end; ++i )
		{
			if ( i>0 && cakes[i].R == cakes[i-1].R )
				continue;
			double _s = sq( cakes[i].R ) + 2*cakes[i].R*cakes[i].H;
			vector<PC> subcakes( cakes.cbegin()+i+1, cakes.cend() );
			sort( subcakes.begin(), subcakes.end(),
				[]( const PC& l, const PC& r )->bool
				{
					const double _l = l.R * l.H;
					const double _r = r.R * r.H;
					return _l > _r;
				}
			);
			_ASSERTE( subcakes.size() >= K-1 );
			for ( int j = 0; j < K - 1; ++j )
				_s += 2 * subcakes[j].R * subcakes[j].H;
			if ( _s > S )
				S = _s;
		}
		S *= M_PI;

		cout << setprecision( 6 ) << fixed << "Case #" << Ntest+1 << ": " << S << endl;
	}

	return 0;
}
