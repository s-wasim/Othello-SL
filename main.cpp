#include "Game.h"

int main() {
	Game obj;
	obj.play();
	if (obj.get_winner() == 'W')
		cout << "WHITE HAS WON!!\n";
	else
		cout << "BLACK HAS WON!!\n";

	return 0;
}