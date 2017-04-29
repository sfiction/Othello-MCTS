#include "MinMaxplayer.h"

namespace Othello{
	pair<int, bool> MinMaxPlayer::calcMinMax(const ChessBoard &board, Color color){
		ull pos = board.getPossibleUll(color);
		if (pos == 0)
			return make_pair(-1, true);

		ChessBoard tb;
		int res = color == BLACK ? -2 : 2, ret, loc = -1;
		for (int i = 0; pos; ++i, pos >>= 1)
			if (pos & 1){
				tb = board, tb.play(color, i);
				if (color == BLACK){
					if (res < (ret = minValue(tb, res, 1)))
						res = ret, loc = i;
				}
				else{
					if (res > (ret = maxValue(tb, -1, res)))
						res = ret, loc = i;
				}
			}
		fprintf(stderr, "+++++++++++++ MinMaxPlayer: color: %s\nresult check = %d, %d\n", color == BLACK ? "BLACK" : "WHITE", res, loc);
		return make_pair(loc, color == BLACK ? res != -1 : res != 1);
	}

	int MinMaxPlayer::minValue(const ChessBoard &board, int a, int b){
		if (board.isFull())
			return board.getResult();

		ull pos = board.getPossibleUll(WHITE);
		if (pos == 0){
			if (board.getPossibleUll(BLACK) == 0)
				return board.getResult();
			else
				return maxValue(board, a, b);
		}

		ChessBoard tb;
		int ret = 1;
		for (int i = 0; pos; ++i, pos >>= 1)
			if (pos & 1){
				tb = board, tb.play(WHITE, i);
				ret = min(ret, maxValue(tb, a, b));
				if (ret <= a)
					return ret;
				b = min(b, ret);
			}
		return ret;
	}

	int MinMaxPlayer::maxValue(const ChessBoard &board, int a, int b){
		if (board.isFull())
			return board.getResult();

		ull pos = board.getPossibleUll(BLACK);
		if (pos == 0){
			if (board.getPossibleUll(WHITE) == 0)
				return board.getResult();
			else
				return minValue(board, a, b);
		}

		ChessBoard tb;
		int ret = -1;
		for (int i = 0; pos; ++i, pos >>= 1)
			if (pos & 1){
				tb = board, tb.play(BLACK, i);
				ret = max(ret, minValue(tb, a, b));
				if (ret >= b)
					return ret;
				a = max(a, ret);
			}
		return ret;
	}
}
