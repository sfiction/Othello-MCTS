#include "round.h"

namespace Othello{
	Round::Round(Player &a, Player &b, const ChessBoard &board, int step, int status):
		A(a), B(b),
		step(step), status(status),
		board(board){
	}

	/**
	 * @return	passed steps and status, [0, 64) loc, -1 failed, -2 already ended
	 */
	int Round::nextStep(){
		if (isEnd())
			return -2;

		int loc = -1;
		if (++step & 1){	// black turn
			loc = A.nextStep(board, BLACK);
			board.play(BLACK, loc);	// without check
		}
		else{	// white turn
			loc = B.nextStep(board, WHITE);
			board.play(WHITE, loc);	// without check
		}
		status += loc == -1;
		if (board.isFull())
			status = 2;
		return loc;
	}

	void Round::nextStep(int loc){
		if (isEnd())
			return;

		if (++step & 1)
			board.play(BLACK, loc);
		else
			board.play(WHITE, loc);
		status += loc == -1;
		if (board.isFull())
			status = 2;
	}

	int Round::play(){
		do{
			nextStep();
		}while (!isEnd());
		return getResult();
	}
}
