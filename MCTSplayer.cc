#include "MCTSplayer.h"

namespace Othello{
/*	MCTSPlayer::Node MCTSPlayer::getNode(){
		if (lst.empty())
			return new Node;
		else{
			auto ret = &lst.back();
			lst.pop_back();
			ret->q = 0, ret->n = 0;
			ret->loc.clear();
			ret->child.clear();
			return ret;
		}
	}

	void MCTSPlayer::delNode(Node *u){
		for (auto &v: child[u])
			delNode(v);
		lst.push_back(u);
	}*/

	MCTSPlayer::Node::Node(const ChessBoard &board, Color color, Node *fa):
		q(0), n(0), fa(fa){
		loc = board.getPossible(color);
		if (loc.size() == 0)
			loc.push_back(-1);
	}

	MCTSPlayer::Node::~Node(){
		for (auto &u: child)
			delete u;
	}

	int MCTSPlayer::Node::expand(const ChessBoard &board, Color color){
		if (loc.size() == child.size())
			return -1;
		else{
			child.push_back(new Node(board, color, this));
			return child.size() - 1;
		}
	}

	double MCTSPlayer::Node::value(){
		const double c = 2.0;
		return (double)q / n + c * sqrt(2.0 * log(fa->n) / n);
	}

	int MCTSPlayer::Node::bestChild(){
		int ret = -1;
		double retVal = -1e300, t;
		for (size_t i = 0; i < loc.size(); ++i)
			if (child[i] != NULL && retVal < (t = child[i]->value()))
				ret = i, retVal = t;
		return ret;
	}

	int MCTSPlayer::Node::bestChildRate(){
		int ret = 0;
		double retVal = -1e300, t;
		for (size_t i = 0; i < loc.size(); ++i)
			if (child[i] != NULL && retVal < (t = 1.0 * child[i]->q / child[i]->n))
				ret = i, retVal = t;
		return ret;
	}

	int MCTSPlayer::nextStep(const ChessBoard &board, Color color){
		Node *root = new Node(board, color, NULL);

		int sign = color == BLACK ? 1 : -1;

		fprintf(stderr, "MCTSPlayer: search start\n");

		const int iterN = 1e3;
		int endTime = clock() + 2000, tot = 0;	// 1s under windows
		RandomPlayer A;
		do{
			for (int iter = 0; iter < iterN; ++iter){
				Round round(A, A, board, (int)color);
				auto u = root;

				/* tree policy */
				int loc;
				for (; u->loc.size() == u->child.size(); u = u->child[loc]){
					loc = u->bestChild();
					round.nextStep(loc);
				}
				loc = u->expand();
				round.nextStep(loc);
				u = u->child[loc];

				/* simulate */
				round.play();

				/* backup */
				int reward = sign * round.getResult();
				for (; u != NULL; u = u->fa){
					++u->n;
					u->q += reward;
				}
			}
			++tot;
		}while (clock() <= endTime);
		fprintf(stderr, "MCTSPlayer: simulate rounds: %d\n", tot * iterN);

		int ret = root->loc[root->bestChildRate()];
		delete root;

		printf("MCTS Result: %d\n", ret);

		return ret;
	}
}

