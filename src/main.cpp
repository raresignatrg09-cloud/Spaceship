#include <raylib.h>
#include "headers/Game.h"

// Initialization
const int screenWidth = 1000;
const int screenHeight = 800;

int main()
{
	Game game(screenWidth, screenHeight, "My Game");
	game.run();
}