/**
 * @file	chessBoard.cc
 * @author	sfiction
 * @date	2017-04-24
 * @version	0.1
 *
 * @brief	Othello chess board implementation
 */
#include <cstdio>
#include "chessBoard.h"

namespace Othello{
	/**
	 * @brief	pretreatment of chess board
	 */
	namespace ChessBoardPretreatment{
		static const int n = 8, m = 1 << n;
		int sel[n][m][m];

		static inline int solve(int a, int b){
			int ret = 0;
			for (int i = 0; i < 6; ++i)
				if (a >> i & b >> (i + 1) & 1){
					for (i += 2; b >> i & 1; ++i);
					ret |= 1 << i & ~(a | b);
				}
			for (int i = 7; i > 1; --i)
				if (a >> i & b >> (i - 1) & 1){
					for (i -= 2; i && b >> i & 1; --i);
					ret |= 1 << i & ~(a | b);
				}
			return ret & 255;
		}

		static void chessBoardPretreatment(){
			static bool done = false;
			if (done)
				return;

			for (int i = m - 1; i >= 0; --i){
				int mask = (m - 1) ^ i;
				for (int j = mask; j > 0; j = (j - 1) & mask)
					sel[0][i][j] = solve(i, j);
				sel[0][i][0] = solve(i, 0);
			}

			for (int k = 1; k < n; ++k){
				int mlow = (1 << k) - 1, mhigh = (m - 1) ^ mlow;
				for (int i = m - 1; i >= 0; --i){
					int ilow = i & mlow, ihigh = i & mhigh;
					int mask = (m - 1) ^ i;
					for (int j = mask; j > 0; j = (j - 1) & mask)
						sel[k][i][j] = sel[0][ihigh][j & mhigh] | sel[0][ilow][j & mlow];
					sel[k][i][0] = sel[0][ihigh][0] | sel[0][ilow][0];;
				}
			}
		}

		/**
		 * @brief	booter of pretreatment of chess board
		 */
		class ChessBoardPretreatmentBooter{
		public:
			ChessBoardPretreatmentBooter(){
				chessBoardPretreatment();
			}
		}chessBoradPretreatmentBooter;
	}

	namespace CBP = ChessBoardPretreatment;

	string ChessBoard::to_string() const{
		string ret("  01234567\n");
		const ull &black = board[0], &white = board[1];
		for (int loc = 0, i = 0; i < 8; ++i){
			ret.push_back('0' + i), ret.push_back(' ');
			for (int j = 0; j < 8; ++j, ++loc)
				ret.push_back(black >> loc & 1 ? 'X' : white >> loc & 1 ? 'O' : '.');
			ret.push_back('\n');
		}
		return ret;
	}

	/**
	 * @brief	test an effective step
	 */
	bool ChessBoard::check(Color color, int loc) const{
		const ull &a = board[color], &b = board[!color];	// bad code

		if (!inRange(loc) || ((a | b) & (1ull << loc)))
			return false;

		const int MASK = ~7;
		for (int i = 0; i < 8; ++i){
			int x = (loc >> 3) + dire[i][0], y = (loc & 7) + dire[i][1], z = loc + dloc[i];
			if (!((x | y) & MASK) && (b >> z & 1)){
				do{
					x += dire[i][0], y += dire[i][1], z += dloc[i];
				}while (!((x | y) & MASK) && (b >> z & 1));
				if (!((x | y) & MASK) && (a >> z & 1))
					return true;
			}
		}
		return false;
	}

	bool ChessBoard::play(Color color, int loc){
		if (loc == -1)	// not an effective step
			return true;

		ull &a = board[color], &b = board[!color];	// bad code
		if (!inRange(loc) || ((a | b) & (1ull << loc)))
			return false;

		const int MASK = ~7;
		ull flip = 0, t;
		for (int i = 0; i < 8; ++i){
			int x = (loc >> 3) + dire[i][0], y = (loc & 7) + dire[i][1], z = loc + dloc[i];
			if (!((x | y) & MASK) && (b >> z & 1)){
				t = 0;
				do{
					t |= 1ull << z;
					x += dire[i][0], y += dire[i][1], z += dloc[i];
				}while (!((x | y) & MASK) && (b >> z & 1));
				if (!((x | y) & MASK) && (a >> z & 1))
					flip |= t;
			}
		}
		if (flip){
			a ^= flip, b ^= flip;	// flip covered chess
			a |= 1ull << loc;	// new chess
			return true;
		}
		else
			return false;
	}

	ull ChessBoard::getPossibleUll(Color color) const{
		ull ret = 0;
		for (int i = 63; i >= 0; --i)
			ret = ret << 1 | check(color, i);
		return ret;
	}

	vector<int> ChessBoard::getPossible(Color color) const{
		vector<int> ret;
		for (int i = 0; i < 64; ++i)
			if (check(color, i))
				ret.push_back(i);
		return ret;
	}
}
