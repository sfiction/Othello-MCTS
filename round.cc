#include "round.h"

namespace Othello{
	Round::Round(Player &a, Player &b):
		A(a), B(b),
		step(0), status(0),
		board(){
	}

	/**
	 * @return	passed steps and status, [0, 64) loc, -1 failed, -2 already ended
	 */
	pair<int, int> Round::nextStep(){
		if (isEnd())
			return make_pair(step, -2);

		int loc = -1;
		if (++step & 1){	// black turn
			loc = A.nextStep(board, BLACK);
			board.play(BLACK, loc);
		}
		else{	// white turn
			puts("???????????");
			loc = B.nextStep(board, WHITE);
			board.play(WHITE, loc);
		}
		status += loc == -1;
		return make_pair(step, loc);
	}
}
