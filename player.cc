#include <vector>
#include "player.h"
#include <windows.h>


namespace Othello{
	int RandomPlayer::nextStep(const ChessBoard &board, Color color){
		vector<int> lst = board.getPossible(color);
		int ret = -1;
		if (lst.size()){
			int t = rand() % lst.size();
			ret = lst[t];
		}
		return ret;
	}
	
	int HumanPlayer::nextStep(const ChessBoard &board, Color color){
		auto ts = board.to_string();
		fprintf(stdout, "%s", ts.c_str());
		fprintf(stdout, "Your color: %s\n", color == BLACK ? "Black" : "White");

		if (board.getPossible(color).size() == 0){
			fputs("No possible steps.\n", stdout);
			return -1;
		}
		int x, y;
		do{
			fscanf(stdin, "%d %d", &x, &y);
		}while (!board.check(color, x << 3 | y));
		return x << 3 | y;
	}
	int GUIPlayer::nextStep(const ChessBoard &board,Color color){
		do{
			printf("in GUIPlayer nextStep!\n");
			fflush(stdout);
			flag = 1;
			printf("GUIPlayer\n");
			while(flag){
				//printf("in while : %d\n",flag);
				//Sleep(1000);
			}
			//f[GUI_x][GUI_y] = color + 1;
		}while(!board.check(color,GUI_y << 3 | GUI_x));
		return GUI_y << 3 | GUI_x;
	}
}
