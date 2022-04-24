#pragma once
#include <iostream>
#include "Board.h"
#include "possibleMoves.h"
class Player;
class Human_Player;
class AI_Player;
#define PLAYER_BLACK 0
#define PLAYER_WHITE 1
using namespace std;

class Game
{
private:
	char currTurn;
	Player** players;
	Board boardObj;
	int bothFail; //integer to calculate if both players unable to move.
	/*
		Above variable is not needed but will significantly reduce
		runtime for each turn as it is necesssary to calculate if the 
		game has ended.
	*/
	//Functions needed in main game loop only.
	bool game_over();
	void do_move(); //AI does this
	bool do_move(possibleMoves x); //Human does this

public:
	Game();

	//Function for main game.
	void play();
	char get_winner() {
		int wP = boardObj.get_pts(WHITE_PEICE);
		int bP = boardObj.get_pts(BLACK_PEICE);
		if (wP > bP)
			return WHITE_PEICE;
		return BLACK_PEICE;
	}

	//Function for AI Only
	Board get_board();
};

