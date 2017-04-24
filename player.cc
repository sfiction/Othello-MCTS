#include <vector>
#include "player.h"

namespace Othello{
	int RandomPlayer::nextStep(const ChessBoard &chessBoard, Color color){
		vector<int> lst = chessBoard.getPossible(color);
		int ret = -1;
		if (lst.size()){
			int t = gen() % lst.size();
			ret = lst[t];
		}
		printf("%d %d\n", color, ret);
		getchar();
		return ret;
	};
}
