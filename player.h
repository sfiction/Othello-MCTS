/**
 * @file	player.h
 * @author	sfiction
 * @date	2017-04-24
 * @version	0.1
 *
 * @brief	Othello player
 */

#ifndef __OTHELLO_PLAYER
#define __OTHELLO_PLAYER

#include <ctime>
#include <random>
#include <windows.h>
#include "basic.h"
#include "chessBoard.h"

extern volatile int GUI_x,GUI_y;
extern volatile int flag;
extern volatile int f[9][9];
namespace Othello{
	using namespace std;

	/**
	 * @brief	player
	 */
	class Player{
	public:
		/*
		 * @return:	[0, 64) if success, otherwise -1
		 */
		virtual int nextStep(const ChessBoard &board, Color color) = 0;
	};

	/**
	 * @brief	random player
	 */
	class RandomPlayer: public Player{
		minstd_rand0 gen;
		
	public:
		RandomPlayer(): gen(time(NULL)){
		}

		int nextStep(const ChessBoard &board, Color color);
	};

	/**
	 * @brief	human player
	 */
	class HumanPlayer: public Player{
	public:
		int nextStep(const ChessBoard &board, Color color);
	};

	/**
	* @brief gui player
	*/
	class GUIPlayer: public Player{
		int nextStep(const ChessBoard &board,Color color);
	};
}

#endif
