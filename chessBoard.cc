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
	void ChessBoard::print() const{
		const ull &black = board[0], &white = board[1];
		for (int loc = 0, i = 0; i < 8; ++i){
			for (int j = 0; j < 8; ++j, ++loc){
				putchar(black >> loc & 1 ? 'X' : white >> loc & 1 ? 'O' : '.');
			}
			puts("");
		}
	}

	/**
	 * @brief	test an effective step
	 */
	bool ChessBoard::check(Color color, int loc) const{
		const ull &a = board[color], &b = board[!color];	// bad code

		if (!inRange(loc) || (a & (1ull << loc)))
			return false;

		return false;
	}

	bool ChessBoard::play(Color color, int loc){
		if (loc == -1)	// not an effective step
			return true;
		if (!check(color, loc))
			return false;

		board[color] |= 1ull << loc;
		return true;


		if (!inRange(loc))
			return false;
		if (!check(color, loc))
			return false;
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
