#pragma once
#include "Game.h"

class Player abstract
{
public:
	virtual void perform_move(Board* boardObj) = 0;
};