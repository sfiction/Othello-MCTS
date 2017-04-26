/**
 * @file	chessBoard.cc
 * @author	sfiction
 * @date	2017-04-24
 * @version	0.1
 *
 * @brief	Othello chess board definition
 */
#ifndef __OTHELLO_CHESSBOARD
#define __OTHELLO_CHESSBOARD

#include <vector>
#include "basic.h"

namespace Othello{
	using namespace std;

	class ChessBoard{
		ull board[2];

		static bool inRange(int x){
			return 0 <= x && x < 64;
		}

	public:
		bool isFull() const{
			return (board[0] | board[1]) == ~0ull;
		}

		ull getBoard(Color flag) const{
			return board[!!flag];
		}

		ull getBlack() const{
			return board[BLACK];
		}

		ull getWhite() const{
			return board[WHITE];
		}

		int countBlack() const{
			return __builtin_popcountll(board[BLACK]);
		}

		int countWhite() const{
			return __builtin_popcountll(board[WHITE]);
		}

		int getResult() const{
			int na = countBlack(), nb = countWhite();
			return na < nb ? -1 : na > nb;
		}

		string to_string() const;
		bool check(Color color, int loc) const;
		bool play(Color color, int loc);
		ull getPossibleUll(Color color) const;
		vector<int> getPossible(Color color) const;

		ChessBoard(){
			board[0] = 1ull << 28 | 1ull << 35;
			board[1] = 1ull << 27 | 1ull << 36;
		}

		ChessBoard(ull black, ull white){
			board[0] = black, board[1] = white;
		}

//		ChessBoard(const vector<int> &manual); todo
	};
}

#endif
