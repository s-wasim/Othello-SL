#pragma once
#include "Player.h"
class AI_Player :
    public Player
{
private:
    possibleMoves bestMove;
    int minimax(char currTurn, Board tempBoard, int Depth, int alpha, int beta);
    void minimax(Board tempBoard, int Depth);
public:
    void perform_move(Board* boardObj) override;
};