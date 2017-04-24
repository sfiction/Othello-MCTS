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
	string ChessBoard::to_string() const{
		string ret;
		const ull &black = board[0], &white = board[1];
		for (int loc = 0, i = 0; i < 8; ++i){
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

	vector<int> ChessBoard::getPossible(Color color) const{
		vector<int> ret;
		for (int loc = 0, i = 0; i < 8; ++i)
			for (int j = 0; j < 8; ++j, ++loc)
				if (check(color, loc))
					ret.push_back(loc);
		return ret;
	}
}
