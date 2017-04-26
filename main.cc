#include "Othello.h"

using namespace Othello;

void speedTestOfRandomPlayer(){
	RandomPlayer a, b;

	const int n = 1e4;
	int cnt = 0;
	for (int iter = 0; iter < n; ++iter){
		Round round(a, b);
		do{
			round.nextStep();
		}while (!round.isEnd());
		cnt += round.getResult();
	}
	fprintf(stderr, "%d\n", cnt);
}

void randomVsHuman(){
	RandomPlayer a;
	HumanPlayer b;
	Round round(a, b);
	do{
		round.nextStep();
	}while (!round.isEnd());
	printf("%d %d\n", round.getBoard().countBlack(), round.getBoard().countWhite());
}

void MCTSTest(){
	RandomPlayer a;
	MCTSPlayer b;

	Round round(b, a);
	do{
		round.nextStep();
		printf("%s\n", round.getBoard().to_string().c_str());
	}while (!round.isEnd());
	printf("%d %d\n", round.getBoard().countBlack(), round.getBoard().countWhite());
}

int main(){
	srand(time(NULL));
//	speedTestOfRandomPlayer();
//	randomVsHuman();
	MCTSTest();
	return 0;
}
