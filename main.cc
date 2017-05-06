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

void MCTSSingleStepTest(){
	MCTSPlayer a;
	ChessBoard board(0x001E0E46426040E1, 0xFE61F1B9BD9FBF1E);
	printf("%s\n", board.to_string().c_str());
	a.nextStep(board, BLACK);
}

void MCTSVsHuman(){
	MCTSPlayer a;
	HumanPlayer b;
	Round round(a, b);
	do{
		round.nextStep();
	}while (!round.isEnd());
	printf("%d %d\n", round.getBoard().countBlack(), round.getBoard().countWhite());
}

void MCTSVsMCTS(){
	MCTSPlayer a;
//	ChessBoard board(0x001E0E46426040E1, 0xFE61F1B9BD9FBF1E);

	Round round(a, a);
	do{
		round.nextStep();
		printf("%s\n", round.getBoard().to_string().c_str());
	}while (!round.isEnd());
	printf("%d %d\n", round.getBoard().countBlack(), round.getBoard().countWhite());
}

void MinMaxTest(){
	MinMaxPlayer a;
	Round round(a, a, ChessBoard(0x9D52E70E0A142040ull, 0x000C1830752A5FBCull), 0);

//	Round round(a, a, ChessBoard(0x9DC3C3243945657Full, 0x003C3CDBC6BA9A80ull), 1);
	
	do{
		round.nextStep();
		printf("%s\n", round.getBoard().to_string().c_str());
	}while (!round.isEnd());
	printf("%d %d\n", round.getBoard().countBlack(), round.getBoard().countWhite());
}

void MinMaxVsMCTS(){
	MCTSPlayer b;
	MCTSMMPlayer a;
	Round round(a, b);
	do{
		round.nextStep();
//		printf("\t\tstep %d\n%s\n", round.currentStep(), round.getBoard().to_string().c_str());
		printf("\t\t\t\t\t\ttime cost = %.3f ms\n", round.getTimeCost());
	}while (!round.isEnd());
	printf("%d %d\n", round.getBoard().countBlack(), round.getBoard().countWhite());
}

//// compete
void GMMCTSMMVsHuman(){
	GRANDMCTSMMPlayer a;
	HumanPlayer b;
	Round round(a, b);

	double tot[2] = {0.0, 0.0};
	do{
		round.nextStep();
		printf("\t\tstep %d\n%s\n", round.currentStep(), round.getBoard().to_string().c_str());
		printf("time cost = %.3f ms\n", round.getTimeCost());
		tot[!round.nextColor()] += round.getTimeCost();
	}while (!round.isEnd());
	printf("%d %d\n", round.getBoard().countBlack(), round.getBoard().countWhite());
	printf("BLACK: %.3f, WHITE: %.3f\n", tot[0], tot[1]);
}

int main(){
	srand(time(NULL));
//	speedTestOfRandomPlayer();
//	randomVsHuman();
//	MCTSTest();
//	MCTSSingleStepTest();
//	MCTSVsHuman();
//	MCTSVsMCTS();
//	MinMaxTest();

	for (int i = 0; i < 100; ++i)
		MinMaxVsMCTS();
	
//	GMMCTSMMVsHuman();
	return 0;
}
