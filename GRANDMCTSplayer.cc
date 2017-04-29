#include "GRANDMCTSPlayer.h"

namespace Othello{
	GRANDMCTSPlayer::GRANDMCTSPlayer(){
		Master = Grandmaster::GetInstance();
	}

	int GRANDMCTSPlayer::nextStep(const ChessBoard &board, Color color){
#ifdef DEBUG
		fprintf(stderr, "GRANDMCTSPlayer: search start\n");
#endif
		vector<pair<int, int> > inst = Master->askGrandmaster(board, color);
		fprintf(stderr, "---[ %d ]---\n", (int)inst.size());
		
		if (board.countBlack() + board.countWhite() - 4 < 15 && inst.size() > 0){
			int id = rand() % inst.size();
			for (size_t i = 0; i < inst.size(); i++)
				if (inst[i].second > inst[id].second)
					id = i;
			int loc = inst[id].first;
			fprintf(stderr, "Hear the elder's saying: step: %d (%d, %d) \n", loc, loc >> 3, loc & 7);
			return loc;
		}

		return MCTSPlayer::nextStep(board, color);
	}

	GRANDMCTSMMPlayer::GRANDMCTSMMPlayer(){
		Master = Grandmaster::GetInstance();
	}

	int GRANDMCTSMMPlayer::nextStep(const ChessBoard &board, Color color){
#ifdef DEBUG
		fprintf(stderr, "GRANDMCTSMMPlayer: search start\n");
#endif
		/// instructions by Grandmasters
		vector<pair<int, int> > inst = Master->askGrandmaster(board, color);
		fprintf(stderr, "---[ %d ]---\n", (int)inst.size());
		
		if (board.countBlack() + board.countWhite() - 4 < 15 && inst.size() > 0){
			int id = rand() % inst.size();
			for (size_t i = 0; i < inst.size(); i++)
				if (inst[i].second > inst[id].second)
					id = i;
			int loc = inst[id].first;
			fprintf(stderr, "Hear the elder's saying: step: %d (%d, %d) \n", loc, loc >> 3, loc & 7);
			return loc;
		}

		return MCTSMMPlayer::nextStep(board, color);
	}
}

