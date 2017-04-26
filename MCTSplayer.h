/**
 * @file	MCTSplayer.h
 * @author	sfiction
 * @date	2017-04-26
 * @version	0.1
 *
 * @brief	Othello player implemented by MCTS
 */

#ifndef __OTHELLO_MCTSPLAYER
#define __OTHELLO_MCTSPLAYER

#include <ctime>
#include <random>
#include "basic.h"
#include "chessboard.h"
#include "player.h"
#include "round.h"

namespace Othello{
	using namespace std;

	/**
	 * @brief	AI implemented by MCTS
	 */
	class MCTSPlayer: public Player{
		struct Node{
			int q, n;
			Node *fa;

			vector<int> loc;
			vector<Node*> child;

			int expand(const ChessBoard &board = ChessBoard(), Color color = BLACK);
			double value();
			int bestChild();
			int bestChildRate();
			Node(const ChessBoard &board = ChessBoard(), Color color = BLACK, Node *fa = NULL);
			~Node();
		};

	public:
		int nextStep(const ChessBoard &board, Color color);
	};
}

#endif

