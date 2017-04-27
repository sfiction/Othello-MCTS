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
			int q, n;	/// total score; total rounds
			Node *fa;	/// father node

			vector<int> loc;	/// available actions (including PASS = -1)
			vector<Node*> child;	/// corresponding child nodes

			/**
			 * @brief	expand next child;
			 * @note	it will also play a step on round
			 */
			int expand(Round &round);

			/**
			 * @brief	calculate the value by UCT
			 * @note	coefficient c should be well selected
			 */
			double value();

			/**
			 * @brief	calculate the win rate
			 * @note	simply q/n
			 */
			double rate();

			/**
			 * @brief	select expanded child with highest value()
			 * @return	offset of slected child
			 */
			int bestChild();

			/**
			 * @brief	select expanded child with highest rate()
			 * @return	offset of selected child
			 */
			int bestChildRate();

			/**
			 * @param	board	to generate possible steps
			 * @param	color	color of next chess
			 * @param	fa	the father node
			 */
			Node(const ChessBoard &board = ChessBoard(), Color color = BLACK, Node *fa = NULL);

			/**
			 * @brief	recursively delete child nodes
			 */
			~Node();
		};

		/**
		 * @brief	evaluate current chess board by MCTS
		 * @reutrn	the root of generated tree
		 */
		Node* MCTSEval(const ChessBoard &board, Color color);

	public:
		int nextStep(const ChessBoard &board, Color color);

		/**
		 * @brief	evaluate the winning percentage of current board & color
		 */
		pair<int, double> evaluate(const ChessBoard &board, Color color);
	};
}

#endif

