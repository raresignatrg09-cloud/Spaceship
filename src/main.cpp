#include <raylib.h>
#include "headers/Game.h"

// Initialization
const int screenWidth = 800;
const int screenHeight = 600;

int main()
{
	Game game(screenWidth, screenHeight, "My Game");
	game.run();
}