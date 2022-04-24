#include "Board.h"

//Constructor
Board::Board() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			mainBoard[i][j] = EMPTY_SPACE;
	mainBoard[3][3] = WHITE_PEICE;
	mainBoard[4][3] = BLACK_PEICE;
	mainBoard[3][4] = BLACK_PEICE;
	mainBoard[4][4] = WHITE_PEICE;
}

//Private Functions
bool Board::check_flip(char colour, int row, int col, int deltaRow, int deltaCol)
{
    char oppColour = WHITE_PEICE;
    if (colour == WHITE_PEICE) oppColour = BLACK_PEICE;

    if ((row < 0) || (row >= 8) || (col < 0) || (col >= 8)) return false;

    if (mainBoard[row][col] == oppColour)
    {
        while ((row >= 0) && (row < 8) && (col >= 0) && (col < 8))
        {
            row += deltaRow;
            col += deltaCol;
            if (mainBoard[row][col] == EMPTY_SPACE) return false;
            if (mainBoard[row][col] == colour) return true;
        }
    }
    return false;
}
void Board::generate_possible_moves(char colour) {
    currPossibleMoves.clear();
    possibleMoves temp;
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {

            if (mainBoard[row][col] != EMPTY_SPACE) continue;
            // Check Up
            if (check_flip(colour, row - 1, col, -1, 0)) goto addInArr;
            // Check Down
            if (check_flip(colour, row + 1, col, 1, 0)) goto addInArr;
            // Check Left
            if (check_flip(colour, row, col - 1, 0, -1)) goto addInArr;
            // Check Right
            if (check_flip(colour, row, col + 1, 0, 1)) goto addInArr;
            // Check Down-Right
            if (check_flip(colour, row + 1, col + 1, 1, 1)) goto addInArr;
            // Check Down-Left
            if (check_flip(colour, row + 1, col - 1, 1, -1)) goto addInArr;
            // Check Top-Right
            if (check_flip(colour, row - 1, col + 1, -1, 1)) goto addInArr;
            // Check Top-Left
            if (check_flip(colour, row - 1, col - 1, -1, -1)) goto addInArr;
            continue;
        addInArr:
            temp.x = row;
            temp.y = col;
            currPossibleMoves.push_back(temp);
		}
	}
}
void Board::change_pieces(char colour, int row, int col, int deltaRow, int deltaCol)
{
    char oppColour = WHITE_PEICE;
    if (colour == WHITE_PEICE)
        oppColour = BLACK_PEICE;
    while (mainBoard[row][col] == oppColour)
    {
        mainBoard[row][col] = colour;
        row += deltaRow;
        col += deltaCol;
    }
}

//Public Functions
void Board::print_board(char colour) {
    system("CLS");
    cout << "OTHELLO BY S-L. o((>ω< ))o" << "\n\n";
	generate_possible_moves(colour);
    currPossibleMoves.shrink_to_fit();
    char arr[8][8];
    for (auto itr : currPossibleMoves) {
        arr[itr.x][itr.y] = 'q';
    }
    cout << "  X ";
    for (int i = 0; i < 8; i++) cout << i + 1 << "   ";
    cout << "\nY\n";
    for (int i = 0; i < 8; i++) {
        cout << i + 1 << "   ";
        for (int j = 0; j < 8; j++) {
            if (arr[i][j] == 'q') {
                cout << POSSIBLE_SP << "   ";
            }
            else {
                cout << mainBoard[i][j] << "   ";
            }
        }
        cout << endl;
    }
}
bool Board::is_move_possible(possibleMoves x) {
    for (auto itr : currPossibleMoves) {
        if (itr.x == x.x && itr.y == x.y)
            return true;
    }
    return false;
}
int Board::get_curr_turn_move_count() {
	return currPossibleMoves.size();
}
void Board::apply_piece(possibleMoves x, char turn) {
    mainBoard[x.x][x.y] = turn;
    if (check_flip(turn, x.x - 1, x.y, -1, 0))
        change_pieces(turn, x.x - 1, x.y, -1, 0);
    // Check Down
    if (check_flip(turn, x.x + 1, x.y, 1, 0))
        change_pieces(turn, x.x + 1, x.y, 1, 0);
    // Check Left
    if (check_flip(turn, x.x, x.y - 1, 0, -1))
        change_pieces(turn, x.x, x.y - 1, 0, -1);
    // Check Right
    if (check_flip(turn, x.x, x.y + 1, 0, 1))
        change_pieces(turn, x.x, x.y + 1, 0, 1);
    // Check Down-Right
    if (check_flip(turn, x.x + 1, x.y + 1, 1, 1))
        change_pieces(turn, x.x + 1, x.y + 1, 1, 1);
    // Check Down-Left
    if (check_flip(turn, x.x + 1, x.y - 1, 1, -1))
        change_pieces(turn, x.x + 1, x.y - 1, 1, -1);
    // Check Top-Right
    if (check_flip(turn, x.x - 1, x.y + 1, -1, 1))
        change_pieces(turn, x.x - 1, x.y + 1, -1, 1);
    // Check Top-Left
    if (check_flip(turn, x.x - 1, x.y - 1, -1, -1))
        change_pieces(turn, x.x - 1, x.y - 1, -1, -1);
}

vector<possibleMoves> Board::get_move_list(char turn) {
    generate_possible_moves(turn);
    return currPossibleMoves;
}
int Board::get_pts(char turn) {
    int pts = 0;
    char oppTurn = BLACK_PEICE;
    if (turn == BLACK_PEICE)
        oppTurn = WHITE_PEICE;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (mainBoard[i][j] == turn)
                pts++;
            else if (mainBoard[i][j] == oppTurn)
                pts--;
        }
    }
    return pts;
}