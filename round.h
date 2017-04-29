#ifndef __OTHELLO_ROUND
#define __OTHELLO_ROUND

#include <vector>

#include "basic.h"
#include "chessBoard.h"
#include "player.h"

namespace Othello{
	using namespace std;

	class RoundBase{
		Player &A, &B;

		int step, status;
		ChessBoard board;

		RoundBase(const RoundBase &t);

	public:
		RoundBase(Player &a, Player &b, const ChessBoard &board = ChessBoard(), int step = 0, int status = 0);

		/**
		 * @return	number of passed step
		 */
		int currentStep() const{
			return step;
		}

		Color nextColor() const{
			return step & 1 ? WHITE : BLACK;
		}

		const ChessBoard& getBoard() const{
			return board;
		}

		bool isEnd() const{
			return status == 2;
		}

		int getResult() const{
			return board.getResult();
		}

		int nextStep();
		void nextStep(int loc);
		int play();
	};

	class Round: public RoundBase{
		double timeCost;

	public:
		Round(Player &a, Player &b, const ChessBoard &board = ChessBoard(), int step = 0, int status = 0):
			RoundBase(a, b, board, step, status),
			timeCost(0){
		}

		/**
		 * @brief	time cost of last step in milisecons
		 */
		double getTimeCost(){
			return timeCost;
		}

		int nextStep(){
			clock_t start = clock();
			int ret = RoundBase::nextStep();
			timeCost = (clock() - start) / (CLOCKS_PER_SEC / 1000.0);
			return ret;
		}

		void nextStep(int loc){
			RoundBase::nextStep(loc);
			timeCost = 0.0;
		}
	};
}

#endif
