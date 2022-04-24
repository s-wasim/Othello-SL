#include "Game.h"
#include "AI_Player.h"
#include "Human_Player.h"
#include "Player.h"

//Private functions
bool Game::game_over() {
	if (bothFail == 2) {
		return true;
	}
	return false;
}
void Game::do_move() {
	players[PLAYER_WHITE]->perform_move(&boardObj);
}
bool Game::do_move(possibleMoves x) {
	if (boardObj.is_move_possible(x)) {
		boardObj.apply_piece(x, BLACK_PEICE);
		return true;
	}
	return false;
}


//Constructor
Game::Game() {
	players = new Player * [2];
	//White Player is AI.
	players[PLAYER_BLACK] = new Human_Player();
	players[PLAYER_WHITE] = new AI_Player();
	//Black player starts always.
	currTurn = BLACK_PEICE;
	bothFail = 0;
}

//Public functions
void Game::play() {
	int x = 0, y = 0;
	while (!game_over()) {
		boardObj.print_board(currTurn);
		if (boardObj.get_curr_turn_move_count() == 0) {
			bothFail++;
			goto changeTurn;
		}
		if (currTurn == BLACK_PEICE) {
			possibleMoves parse;
			try {
				do {
					//Keeps looping if x or y out of bounds
					cout << "\nON FALSE INPUT, REPEATS";
					cout << "\nInput X: "; cin >> y;
					cout << "Input Y: "; cin >> x;
				} while ((x <= 0 && x > 8) || (y <= 0 && x > 8));
				parse.x = x - 1; parse.y = y - 1; //Setting to work with arrays.
			}
			catch (logic_error) {
				cout << "FATAL INPUT ERROR, EXITTING NOW!\n";
				return;
			}
			if (!do_move(parse)) continue;
			bothFail = 0;
		}
		else {
			do_move();
			bothFail = 0;
		}
	changeTurn:
		/*
			Change turns because move valid.
			OR
			Change turns because move not possible
		*/
		if (currTurn == BLACK_PEICE) currTurn = WHITE_PEICE;
		else currTurn = BLACK_PEICE;
	}
}

//AI Function
Board Game::get_board() {
	return boardObj;
}