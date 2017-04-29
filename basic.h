#ifndef __OTHELLO_BASIC
#define __OTHELLO_BASIC

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <vector>

namespace Othello{
	typedef long long ll;
	typedef unsigned long long ull;

	enum Color{
		BLACK, WHITE
	};

	enum Choice{
		PASS = -1
	};

	const int dire[8][2] = {-1, 0, -1, 1, 0, 1, 1, 1, 1, 0, 1, -1, 0, -1, -1, -1};
	const int dloc[8] = {-8, -7, 1, 9, 8, 7, -1, -9};
	const int MSRatio = CLOCKS_PER_SEC / 1000;
}

#endif

