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
		/**
		 * @brief	check the chess board if ull or not
		 */
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

		int count() const{
			return __builtin_popcountll(board[BLACK] | board[WHITE]);
		}

		int countBlack() const{
			return __builtin_popcountll(board[BLACK]);
		}

		int countWhite() const{
			return __builtin_popcountll(board[WHITE]);
		}

		/**
		 * @brief	the score (1, 0, -1) of Black (first player)
		 */
		int getResult() const{
			int na = countBlack(), nb = countWhite();
			return na < nb ? -1 : na > nb;
		}

		/**
		 * @brief	ASCII graph of current chess board
		 */
		string to_string() const;

		/**
		 * @brief	check the step is valid or not
		 */
		bool check(Color color, int loc) const;

		/**
		 * @brief	play a step
		 * @retVal	true	valid and played
		 * @retVal	false	invalid
		 */
		bool play(Color color, int loc);

		/**
		 * @brief	possible steps of color
		 * @return	(ret >> (x << 3 | y) & 1) indicate its availability
		 */
		ull getPossibleUll(Color color) const;
		ull getPossibleUllOld(Color color) const;

		ull haveStep(Color color) const{
			return getPossibleUll(color) != 0;
		}

		/**
		 * @brief	possible steps of color
		 * @return	location is (ret[i] >> 3, ret[i] & 7)
		 */
		vector<int> getPossible(Color color) const;
		vector<int> getPossibleOld(Color color) const;

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
