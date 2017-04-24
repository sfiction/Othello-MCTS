#ifndef __OTHELLO_ROUND
#define __OTHELLO_ROUND

#include <vector>

#include "basic.h"
#include "chessboard.h"
#include "player.h"

namespace Othello{
	using namespace std;

	class Round{
		Player &A, &B;

		int step, status;
		ChessBoard board;

		Round(const Round &t);
		
	public:
		Round(Player &a, Player &b);

		/**
		 * @return	number of passed step
		 */
		int currentStep() const{
			return step;
		}

		const ChessBoard& getBoard() const{
			return board;
		}

		bool isEnd(){
			return status == 2;
		}

		pair<int, int> nextStep();
	};
}

#endif
