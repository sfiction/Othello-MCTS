#include "round.h"

namespace Othello{
	RoundBase::RoundBase(Player &a, Player &b, const ChessBoard &board, int step, int status):
		A(a), B(b),
		step(step), status(status),
		board(board){
	}

	/**
	 * @return	passed steps and status, [0, 64) loc, -1 failed, -2 already ended
	 */
	int RoundBase::nextStep(){
		if (isEnd())
			return -2;

		int loc = -1;
		if (++step & 1)	// black turn
			board.play(BLACK, loc = A.nextStep(board, BLACK));	// without check
		else	// white turn
			board.play(WHITE, loc = B.nextStep(board, WHITE));	// without check
		if (loc == -1)
			++status;
		else
			status = 0;
		if (board.isFull())
			status = 2;
		return loc;
	}

	void RoundBase::nextStep(int loc){
		if (isEnd())
			return;

		if (++step & 1)
			board.play(BLACK, loc);
		else
			board.play(WHITE, loc);
		if (loc == -1)
			++status;
		else
			status = 0;
		if (board.isFull())
			status = 2;
	}

	int RoundBase::play(){
		do{
			nextStep();
		}while (!isEnd());
		return getResult();
	}
}
