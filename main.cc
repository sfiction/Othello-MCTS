#include "Othello.h"

using namespace Othello;

int main(){
	RandomPlayer a, b;
	Round round(a, b);

	round.getBoard().print();
	do{
		round.nextStep();
		round.getBoard().print();
	}while (!round.isEnd());
	return 0;
}
