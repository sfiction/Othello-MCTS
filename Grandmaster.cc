#include "Grandmaster.h"

namespace Othello{
	Grandmaster::Grandmaster(){
		// init the map
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 2; j++){
				manual[i][j].clear();
			}
		char *s = new char[222];
		FILE *fin = fopen("Chess_manual-WThor-GlobalPartial-Zip.txt", "r"); // choose the library
		while (fscanf(fin, "%s", s) != EOF){ // get one round
			ChessBoard *board = new ChessBoard();
			int l = strlen(s);
			// simulate the round and get the winner
			for (int i = 0, j = 0, c = 0; i < l; i += 2, ++j){
				int x = s[i] - 'a', y = s[i + 1] - '1';
				int loc = (x << 3) | y;
				if (!board->play((Color)c, loc)){
					c ^= 1;
					board->play((Color)c, loc);
				}
				c ^= 1;
			}
			// use four board to represent four different transform
			ChessBoard *board1 = new ChessBoard();
			ChessBoard *board2 = new ChessBoard();
			ChessBoard *board3 = new ChessBoard();
			ChessBoard *board4 = new ChessBoard();
			// simulate the first 15 steps and save the state
			for (int i = 0, j = 0, c = 0; i < l && j < 15; i += 2, ++j){
				// get the position
				int x = s[i] - 'a', y = s[i + 1] - '1';
				int loc = (x << 3) | y;
				PUU pre1 = PUU(board1->getBlack(), board1->getWhite());
				// check who will make this step and make it
				if (board1->play((Color)c, loc)){
					manual[j][c][MTD(pre1, loc)]++;
					manual[j][c][MTD(PUU(board2->getBlack(), board2->getWhite()), (y << 3) | x)]++;
					manual[j][c][MTD(PUU(board3->getBlack(), board3->getWhite()), ((7 - x) << 3) | (7 - y))]++;
					manual[j][c][MTD(PUU(board4->getBlack(), board4->getWhite()), ((7 - y) << 3) | (7 - x))]++;
					board2->play((Color)c, (y << 3) | x);
					board3->play((Color)c, ((7 - x) << 3) | (7 - y));
					board4->play((Color)c, ((7 - y) << 3) | (7 - x));
					c ^= 1;
				}
				else{
					c ^= 1;
					manual[j][c][MTD(pre1, loc)]++;
					manual[j][c][MTD(PUU(board2->getBlack(), board2->getWhite()), (y << 3) | x)]++;
					manual[j][c][MTD(PUU(board3->getBlack(), board3->getWhite()), ((7 - x) << 3) | (7 - y))]++;
					manual[j][c][MTD(PUU(board4->getBlack(), board4->getWhite()), ((7 - y) << 3) | (7 - x))]++;
					board1->play((Color)c, loc);
					board2->play((Color)c, (y << 3) | x);
					board3->play((Color)c, ((7 - x) << 3) | (7 - y));
					board4->play((Color)c, ((7 - y) << 3) | (7 - x));
					c ^= 1;
				}
			}
		}
		/*
		puts("= -");
		for (int i = 0; i < 60; i++)
			for (int j = 0; j < 2; j++){
				for (auto &k : manual[i][j]){
					assert(__builtin_popcountll(k.first.first.first | k.first.first.second) == i + 4);
					fprintf(stdout, "%s\n, (%d, %d), %d, color(%d), cnt: %d, %llu, %llu\n", ChessBoard(k.first.first.first, k.first.first.second).to_string().c_str(), k.first.second >> 3, k.first.second & 7, k.second, j, i, k.first.first.first, k.first.first.second);
				}
			}
		*/
		puts("Master prepare done.");
		
	}
	
	Grandmaster* Grandmaster::gmInstance = NULL;
	map<MTD, int> Grandmaster::manual[60][2];
	
	Grandmaster* Grandmaster::GetInstance(){
		// when the class is visited for the first time, init the map from the library.
		if (gmInstance == NULL)
			gmInstance = new Grandmaster();
		return gmInstance;
	}

	vector<pair<int, int> > Grandmaster::askGrandmaster(const ChessBoard &board, Color color){
		// get the first index
		int cnt = board.countBlack() + board.countWhite() - 4;
		vector<pair<int, int> > q;
		PUU sta = PUU(board.getBlack(), board.getWhite());
		
		//printf("Fuck::\n%s\n %d %d\n", board.to_string().c_str(), cnt, (int)color);
		
		// find the first state that suit the current state
		auto k = manual[cnt][(int)color].lower_bound(MTD(sta, -1));
		
		//printf("[%llu, %llu], %d %d\n\n", k->first.first.first, k->first.first.second, k->first.second, k->second);
		
		// while the state is legal, put the strategy in the vector
		while(k->first.first == sta){
			q.push_back(make_pair(k->first.second, k->second));
			k++;
		}
		return q;
	}
}
