/**
 * @file	GRANDMCTSPlayer.h
 * @author	Marisa
 * @date	2017-04-27
 * @version	0.1
 *
 * @brief	Othello player implemented by MCTS and instructed by Grandmasters
 */

#ifndef __OTHELLO_GRANDMCTSPLAYER
#define __OTHELLO_GRANDMCTSPLAYER

#include <ctime>
#include <random>
#include "basic.h"
#include "chessboard.h"
#include "player.h"
#include "round.h"
#include "Grandmaster.h"
#include "MCTSplayer.h"

namespace Othello{
	using namespace std;
	
	/**
	 * @brief	AI implemented by MCTS instructed by Grandmasters 
	 */
	class GRANDMCTSPlayer: public MCTSPlayer{
		Grandmaster* Master;
		
	public:
		GRANDMCTSPlayer();
		int nextStep(const ChessBoard &board, Color color);
	};
	
	/**
	 * @brief	AI implemented by MCTS & MM instructed by Grandmasters 
	 */
	class GRANDMCTSMMPlayer: public MCTSMMPlayer{
		Grandmaster* Master;
		
	public:
		GRANDMCTSMMPlayer();
		int nextStep(const ChessBoard &board, Color color);
	};
}

#endif

