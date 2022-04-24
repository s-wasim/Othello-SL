#pragma once
#include "Player.h"
class Human_Player :
    public Player
{
    void perform_move(Board* boardObj) override {}
};