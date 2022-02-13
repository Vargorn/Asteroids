#include "Game.h"
#include<time.h>
int main() {

	//init game engine
	srand(static_cast<unsigned>(time(0)));
	Game game;


	while (game.getWindowIsOpen()) { //game loop

		game.update(); // update
		game.render(); //render

	}
	return 1;
}