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
		else{
			random_shuffle(loc.begin(), loc.end());
		}
	}

	MCTSPlayer::Node::~Node(){
		for (auto &u: child)
			delete u;
	}

	int MCTSPlayer::Node::expand(Round &round){
		if (loc.size() == child.size())
			return -1;
		else{
			int ret = child.size();
			round.nextStep(loc[ret]);
			child.push_back(new Node(round.getBoard(), round.nextColor(), this));
			return ret;
		}
	}

	double MCTSPlayer::Node::value(){
		const double c = 5.0;
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
#define DEBUG
#ifdef DEBUG
		fprintf(stderr, "MCTSPlayer: search start\n");
#endif

		const int iterN = 1e3;
		int endTime = clock() + 100, tot = 0;	// 1s under windows
		RandomPlayer A;
		do{
			for (int iter = 0; iter < iterN; ++iter){
				Round round(A, A, board, (int)color);
				auto u = root;

				/* tree policy */
				int id;
				for (; !round.isEnd() && u->loc.size() == u->child.size(); u = u->child[id]){
					id = u->bestChild();
					round.nextStep(u->loc[id]);
				}
				
				int sign = round.nextColor() == color ? -1 : 1;
				if (!round.isEnd()){
					sign = -sign;
					id = u->expand(round);
					u = u->child[id];
					/* simulate */
					round.play();
				}

				/* backup */
				int reward = round.getResult();
				for (; u != NULL; u = u->fa){
					++u->n;
					u->q += sign * reward;
					sign = -sign;
				}
			}
			++tot;
		}while (clock() <= endTime);

		int id = root->bestChildRate();
		int loc = root->loc[id];
		
#ifdef DEBUG
		double ratio = 1.0 * root->child[id]->q / root->child[id]->n;
		fprintf(stderr, "MCTSPlayer: simulate rounds: %d\n", tot * iterN);
		fprintf(stderr, "MCTSPlayer: step: %d (%d, %d), ratio: %.8f\n", loc, loc >> 3, loc & 7, ratio);
		
		for (size_t i = 0; i < root->loc.size(); ++i){
			fprintf(stderr, "(%d, %d), ", root->child[i]->q, root->child[i]->n);
		}
		fprintf(stderr, "\n");
#endif
		
		delete root;

		return loc;
	}
}
