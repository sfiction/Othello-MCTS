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
#include "basic.h"
#include "chessboard.h"

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
		virtual int nextStep(const ChessBoard &chessBoard, Color color) = 0;
	};

	/**
	 * @brief	random player
	 */
	class RandomPlayer: public Player{
		minstd_rand0 gen;
		
	public:
		RandomPlayer(): gen(time(NULL)){
		}

		int nextStep(const ChessBoard &chessBoard, Color color);
	};
}

#endif
