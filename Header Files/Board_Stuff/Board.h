#pragma once
#define EMPTY_SPACE '_'
#define BLACK_PEICE 'B'
#define WHITE_PEICE 'W'
#define POSSIBLE_SP 'O'
#include <iostream>
#include <vector>
#include "possibleMoves.h"
using namespace std;


class Board
{
private:
	char mainBoard[8][8];
	vector<possibleMoves> currPossibleMoves;
	bool check_flip(char colour, int row, int col, int deltaRow, int deltaCol);
	void generate_possible_moves(char colour); //Generate a list of all possible moves
	void change_pieces(char colour, int row, int col, int deltaRow, int deltaCol); //flips all neighbouring pieces
	
public:
	Board();
	Board(Board& x) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				mainBoard[i][j] = x.mainBoard[i][j];
			}
		}
		currPossibleMoves = x.currPossibleMoves;
	}

	void print_board(char colour);
	bool is_move_possible(possibleMoves x); //Checks from list only
	void apply_piece(possibleMoves x, char turn); //places new piece on board
	int get_curr_turn_move_count(); //Returns possible move count
	
	//Function for AI Only.
	vector<possibleMoves> get_move_list(char turn);
	int get_pts(char turn);
};