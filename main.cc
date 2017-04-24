#include "Othello.h"

using namespace Othello;

int main(){
	srand(time(NULL));
	RandomPlayer a, b;

	const int n = 1e4;
	int cnt = 0;
	for (int iter = 0; iter < n; ++iter){
		Round round(a, b);
		do{
			round.nextStep();
//			round.getBoard().print();
//			getchar();
		}while (!round.isEnd());
		cnt += round.getResult();
//		printf("%d %d\n", round.getBoard().countBlack(), round.getBoard().countWhite());
	}
	fprintf(stderr, "%d\n", cnt);
	return 0;
}
