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

	MCTSPlayer::Node::Node(){
	}

	MCTSPlayer::Node::~Node(){
		for (auto &u: child)
			delete u;
	}

	MCTSPlayer::Node* MCTSPlayer::Node::expand(){
		if (loc.size() == child.size())
			return NULL;
		else{
			child.push_back(new Node);
			return child.back();
		}
	}

	double MCTSPlayer::Node::value(){
		const double c = 2.0;
		return (double)q / n + c * sqrt(2.0 * log(fa->n) / n);
	}

	int MCTSPlayer::Node::bestChild(){
		int ret = -1;
		double retVal = -1, t;
		for (size_t i = 0; i < loc.size(); ++i)
			if (child[i] != NULL && retVal < (t = child[i]->value()))
				ret = i, retVal = t;
		return ret;
	}

	int MCTSPlayer::Node::bestChildRate(){
		int ret = 0;
		double retVal = -1, t;
		for (size_t i = 0; i < loc.size(); ++i)
			if (child[i] != NULL && retVal < (t = 1.0 * child[i]->q / child[i]->n))
				ret = i, retVal = t;
		return ret;
	}

	int MCTSPlayer::nextStep(const ChessBoard &board, Color color){
		Node *root = new Node;

		const int iterN = 1e3;
		unsigned endTime = clock() + 1000, tot = 0;	// 1s under windows
		RandomPlayer A;
		do{
			for (int iter = 0; iter < iterN; ++iter){
				Round round(A, A, board, (int)color);

				auto u = root;
				for (int loc; u->loc.size() == u->child.size(); u = u->child[u->bestChild()]){
					loc = u->bestChild();
					round.nextStep(loc);
				}
				u = u->expand();
			}
		}while (clock() + endTime);
		fprintf(stderr, "MCTSPlayer: simulate rounds: %u\n", tot * iterN);

		int ret = root->bestChildRate();
		delete root;
		return ret;
	}
}

