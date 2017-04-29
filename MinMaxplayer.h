/**
 * @file	MinMaxplayer.h
 * @author	sfiction
 * @date	2017-04-28
 * @version	0.1
 *
 * @brief	Othello player implemented by Min-Max, with alpha-beta optimization
 */

#ifndef __OTHELLO_MINMAXPLAYER
#define __OTHELLO_MINMAXPLAYER

#include <random>
#include "basic.h"
#include "chessboard.h"
#include "player.h"
#include "round.h"

namespace Othello{
	using namespace std;

	/**
	 * @brief	AI implemented by Min-Max
	 */
	class MinMaxPlayer: virtual public Player{
		int lastLoc;

	protected:
		static pair<int, bool> calcMinMax(const ChessBoard &board, Color color);
		static int minValue(const ChessBoard &board, int a, int b);
		static int maxValue(const ChessBoard &board, int a, int b);

	public:
		int nextStep(const ChessBoard &board, Color color){
			return calcMinMax(board, color).first;
		}
	};
}

#endif
