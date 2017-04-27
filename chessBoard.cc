/**
 * @file	chessBoard.cc
 * @author	sfiction
 * @date	2017-04-24
 * @version	0.1
 *
 * @brief	Othello chess board implementation
 */
#include <cassert>
#include <cstdio>
#include "chessBoard.h"

namespace Othello{
	/**
	 * @brief	pretreatment of chess board
	 */
	namespace ChessBoardPretreatment{
		inline ull transColToRow(ull a){
			a = (a & 0xf0f0f0f00f0f0f0full) | (a << 28 & 0x0f0f0f0f00000000ull) | (a >> 28 & 0x00000000f0f0f0f0ull);
			a = (a & 0xcccc3333cccc3333ull) | (a << 14 & 0x3333000033330000ull) | (a >> 14 & 0x0000cccc0000ccccull);
			return (a & 0xaa55aa55aa55aa55ull) | (a << 7 & 0x5500550055005500ull) | (a >> 7 & 0x00aa00aa00aa00aaull);
		}

		inline ull transMajorDiagToRow(ull a){
			a = (a & 0x0f0f0f0f0f0f0f0full) | (a << 32 & 0xf0f0f0f000000000ull) | (a >> 32 & 0x00000000f0f0f0f0ull);
			a = (a & 0x3333333333333333ull) | (a << 48 & 0xcccc000000000000ull) | (a >> 16 & 0x0000ccccccccccccull);
			return (a & 0x5555555555555555ull) | (a << 56 & 0xaa00000000000000ull) | (a >> 8 & 0x00aaaaaaaaaaaaaaull);
		}

		inline ull transMinorDiagToRow(ull a){
			a = (a & 0x5555555555555555ull) | (a << 8 & 0xaaaaaaaaaaaaaa00ull) | (a >> 56 & 0x00000000000000aaull);
			a = (a & 0x3333333333333333ull) | (a << 16 & 0xcccccccccccc0000ull) | (a >> 48 & 0x000000000000ccccull);
			return (a & 0x0f0f0f0f0f0f0f0full) | (a << 32 & 0xf0f0f0f000000000ull) | (a >> 32 & 0x00000000f0f0f0f0ull);
		}

		static const int n = 8, m = 1 << n;
		unsigned  sel[n][m][m];

		static inline unsigned solve(int a, int b){
			int ret = 0;
			for (int i = 0; i < 6; ++i)
				if (a >> i & b >> (i + 1) & 1){
					for (i += 2; b >> i & 1; ++i);
					ret |= 1 << i-- & ~(a | b);
				}
			for (int i = 7; i > 1; --i)
				if (a >> i & b >> (i - 1) & 1){
					for (i -= 2; i && b >> i & 1; --i);
					ret |= 1 << i++ & ~(a | b);
				}
			return ret & 255;
		}

		static void print(ull t){
			puts("  01234567");
			for (int loc = 0, i = 0; i < 8; ++i){
				printf("%c ", '0' + i);
				for (int j = 0; j < 8; ++j, ++loc)
					putchar(t >> loc & 1 ? '*' : '_');
				puts("");
			}
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
				int mlow = (1 << n - k) - 1, mhigh = (m - 1) ^ mlow;
				for (int i = m - 1; i >= 0; --i){
					int ilow = i & mlow, ihigh = i & mhigh;
					int mask = (m - 1) ^ i;
					for (int j = mask; j > 0; j = (j - 1) & mask)
						sel[k][i][j] = sel[0][ihigh][j & mhigh] & mhigh | sel[0][ilow][j & mlow] & mlow;
					sel[k][i][0] = sel[0][ihigh][0] | sel[0][ilow][0];;
				}
			}

			// test data for pretreatment
/*			ull t = 0x0003001000000004ull;
			print(t);
			print(transColToRow(t));
			print(transColToRow(transColToRow(t)));
			print(transMajorDiagToRow(t));
			print(transMajorDiagToRow(transMinorDiagToRow(t)));*/
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

	// old version of getPossible
 	ull ChessBoard::getPossibleUllOld(Color color) const{
		ull ret = 0;
		for (int i = 63; i >= 0; --i)
			ret = ret << 1 | check(color, i);
		return ret;
	}

	vector<int> ChessBoard::getPossibleOld(Color color) const{
		vector<int> ret;
		for (int i = 0; i < 64; ++i)
			if (check(color, i))
				ret.push_back(i);
		return ret;
	}


	ull ChessBoard::getPossibleUll(Color color) const{
		using namespace ChessBoardPretreatment;
		ull ta = board[color], tb = board[!color];	// bad code
		ull ret = sel[0][ta & 0xff][tb & 0xff] | sel[0][ta >> 8 & 0xff][tb >> 8 & 0xff] << 8
				| sel[0][ta >> 16 & 0xff][tb >> 16 & 0xff] << 16 | sel[0][ta >> 24 & 0xff][tb >> 24 & 0xff] << 24
				| (ull)(sel[0][ta >> 32 & 0xff][tb >> 32 & 0xff] | sel[0][ta >> 40 & 0xff][tb >> 40 & 0xff] << 8
				| sel[0][ta >> 48 & 0xff][tb >> 48 & 0xff] << 16 | sel[0][ta >> 56 & 0xff][tb >> 56 & 0xff] << 24) << 32;

		ull a = transColToRow(ta), b = transColToRow(tb);
		ret |= transColToRow(sel[0][a & 0xff][b & 0xff] | sel[0][a >> 8 & 0xff][b >> 8 & 0xff] << 8
				| sel[0][a >> 16 & 0xff][b >> 16 & 0xff] << 16 | sel[0][a >> 24 & 0xff][b >> 24 & 0xff] << 24
				| (ull)(sel[0][a >> 32 & 0xff][b >> 32 & 0xff] | sel[0][a >> 40 & 0xff][b >> 40 & 0xff] << 8
				| sel[0][a >> 48 & 0xff][b >> 48 & 0xff] << 16 | sel[0][a >> 56 & 0xff][b >> 56 & 0xff] << 24) << 32);
		
		a = transMajorDiagToRow(ta), b = transMajorDiagToRow(tb);
		ret |= transMinorDiagToRow(sel[0][a & 0xff][b & 0xff] | sel[1][a >> 8 & 0xff][b >> 8 & 0xff] << 8
				| sel[2][a >> 16 & 0xff][b >> 16 & 0xff] << 16 | sel[3][a >> 24 & 0xff][b >> 24 & 0xff] << 24
				| (ull)(sel[4][a >> 32 & 0xff][b >> 32 & 0xff] | sel[5][a >> 40 & 0xff][b >> 40 & 0xff] << 8
				| sel[6][a >> 48 & 0xff][b >> 48 & 0xff] << 16 | sel[7][a >> 56 & 0xff][b >> 56 & 0xff] << 24) << 32);

		a = transMinorDiagToRow(ta), b = transMinorDiagToRow(tb);
		ret |= transMajorDiagToRow(sel[7][a >> 0 & 0xff][b >> 0 & 0xff] << 0 | sel[6][a >> 8 & 0xff][b >> 8 & 0xff] << 8
				| sel[5][a >> 16 & 0xff][b >> 16 & 0xff] << 16 | sel[4][a >> 24 & 0xff][b >> 24 & 0xff] << 24
				| (ull)(sel[3][a >> 32 & 0xff][b >> 32 & 0xff] | sel[2][a >> 40 & 0xff][b >> 40 & 0xff] << 8
				| sel[1][a >> 48 & 0xff][b >> 48 & 0xff] << 16 | sel[0][a >> 56 & 0xff][b >> 56 & 0xff] << 24) << 32);
		return ret;
	}

	vector<int> ChessBoard::getPossible(Color color) const{
		ull res = getPossibleUll(color);
		vector<int> ret;
		for (int i = 0; res; ++i, res >>= 1)
			if (res & 1)
				ret.push_back(i);
		return ret;
	}
}
