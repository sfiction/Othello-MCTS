/**
 * @file	Grandmaster.h
 * @author	Marisa
 * @date	2017-04-27
 * @version	0.1
 *
 * @brief	Worldwide Grandmasters 
 */

#ifndef __OTHELLO_GRANDMASTER
#define __OTHELLO_GRANDMASTER

#include <ctime>
#include <map>
#include <cstring>
#include <cassert>
#include "basic.h"
#include "chessBoard.h"
#include "player.h"
#include "round.h"

namespace Othello{
	using namespace std;

	typedef pair<ull, ull> PUU;
	typedef pair<PUU, int> MTD;
	/**
	 * @brief	Grandmasters will give you some advise when you facing challenges. 
	 */
	class Grandmaster {
		Grandmaster();
		static Grandmaster * gmInstance;	/// the point of the singleton class
		static map<MTD, int> manual[60][2];	/// map to store the strategy for different chessboard

	public:
		/**
		 * @brief	get the point of the class or init the class when first use
		 * @return	the point
		 */
		static Grandmaster * GetInstance();
		/**
		 * @brief	query the strategy for some chessboard
		 * @return	the strategy
		 */
		static vector<pair<int, int> > askGrandmaster(const ChessBoard &board, Color color);
	};
}

#endif

