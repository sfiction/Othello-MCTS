/**
 * @file	MCTSplayer.h
 * @author	sfiction
 * @date	2017-04-26
 * @version	0.1
 *
 * @brief	Othello player implemented by MCTS
 */

#ifndef __OTHELLO_PLAYER
#define __OTHELLO_PLAYER

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

			Node* expand();
			double value();
			int bestChild();
			int bestChildRate();
			Node();
			~Node();
		};
		vector<Node*> lst;

		Node* getNode();
		void delNode();

		static childValue();

	public:
		int nextStep(const ChessBoard &board, Color color);
		~MCTSPlayer();
	};
}

#endif

