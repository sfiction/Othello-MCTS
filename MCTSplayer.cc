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
		if (loc.size() == 0)	// no possible steps
			loc.push_back(-1);
		else{
			// randomly select next child to be expanded
			random_shuffle(loc.begin(), loc.end());
		}
	}

	MCTSPlayer::Node::~Node(){
		// recursively deconstruct nodes
		for (auto &u: child)
			delete u;
	}

	int MCTSPlayer::Node::expand(RoundBase &round){
		if (loc.size() == child.size())	// all childs has been expanded
			return -1;
		else{
			int ret = child.size();
			// expand a node and play corresponded step in round
			round.nextStep(loc[ret]);
			child.push_back(new Node(round.getBoard(), round.nextColor(), this));
			return ret;
		}
	}

	double MCTSPlayer::Node::value(){	// UCB tree Policy
		const double c = 5.0;
		return (double)q / n + c * sqrt(2.0 * log(fa->n) / n);
	}

	double MCTSPlayer::Node::rate(){	// winning ratio
		return (double)q / n;
	}

	int MCTSPlayer::Node::bestChild(){
		int ret = 0;
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
			if (child[i] != NULL && retVal < (t = child[i]->rate()))
				ret = i, retVal = t;
		return ret;
	}

	MCTSPlayer::Node* MCTSPlayer::MCTSEval(const ChessBoard &board, Color color, int timeLimit){	// in miliseconds
#ifdef DEBUG
		fprintf(stderr, "MCTSPlayer: search start, color = %s\n", color == BLACK ? "Black" : "White");
#endif
		Node *root = new Node(board, color, NULL);

		timeLimit *= MSRatio;
		const int iterN = 1e3;
		clock_t startTime = clock();
		int tot = 0;
		RandomPlayer A;
		do{
			for (int iter = 0; iter < iterN; ++iter){
				RoundBase round(A, A, board, (int)color);
				auto u = root;

				/* tree policy */
				int id;
				for (; !round.isEnd() && u->loc.size() == u->child.size(); u = u->child[id]){
					id = u->bestChild();
					round.nextStep(u->loc[id]);
				}
				
				int sign = round.nextColor() == BLACK ? -1 : 1;
				if (!round.isEnd()){	// it's unterminal state
					sign = -sign;
					id = u->expand(round);
					u = u->child[id];
					/* simulation */
					round.play();
				}

				/* backpropagation */
				int reward = round.getResult();
				for (; u != NULL; u = u->fa){
					++u->n;
					u->q += sign * reward;
					sign = -sign;
				}
			}
			++tot;
		}while ((int)(clock() - startTime) <= timeLimit);
#ifdef DEBUG
		fprintf(stderr, "MCTSPlayer: simulate rounds: %d\n", tot * iterN);
#endif
		return root;
	}

	int MCTSPlayer::nextStep(const ChessBoard &board, Color color){
		if (!board.haveStep(color))
			return -1;


		auto root = MCTSEval(board, color);
		int id = root->bestChildRate(), loc = root->loc[id];

#ifdef DEBUG
		double ratio = root->child[id]->rate();
		fprintf(stderr, "MCTSPlayer: step: %d (%d, %d), ratio: %.8f\n", loc, loc >> 3, loc & 7, ratio);
		
		for (size_t i = 0; i < root->loc.size(); ++i){
			fprintf(stderr, "(%d, %d), ", root->child[i]->q, root->child[i]->n);
		}
		fprintf(stderr, "\n");
#endif

		delete root;

		return loc;
	}

	pair<int, double> MCTSPlayer::evaluate(const ChessBoard &board, Color color, int timeLimit){
		auto root = MCTSEval(board, color, timeLimit);
		int id = root->bestChildRate(), loc = root->loc[id];

#ifdef DEBUG
		double ratio = root->child[id]->rate();
		fprintf(stderr, "MCTSPlayer: step: %d (%d, %d), ratio: %.8f\n", loc, loc >> 3, loc & 7, ratio);
		
		for (size_t i = 0; i < root->loc.size(); ++i){
			fprintf(stderr, "(%d, %d), ", root->child[i]->q, root->child[i]->n);
		}
		fprintf(stderr, "\n");
#endif

		double rate = root->child[id]->rate();
		delete root;
		return make_pair(loc, rate);
	}

	int MCTSMMPlayer::nextStep(const ChessBoard &board, Color color){
		if (!board.haveStep(color))
			return -1;
		const int timeLimit = 100;
		// 17 or less empty location remain
		if (64 - board.count() <= 17){
			int startTime = clock();
			auto res = MinMaxPlayer::calcMinMax(board, color);
			if (res.second)
				return res.first;
			else // struggle when it will lose
				return MCTSPlayer::evaluate(board, color, timeLimit - (clock() - startTime) / MSRatio).first;
		}
		else
			return MCTSPlayer::evaluate(board, color, timeLimit).first;
	}
}

