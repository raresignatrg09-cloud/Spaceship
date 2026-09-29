#pragma once
#include <raylib.h>
#include <vector>

#include "Player.h"
#include "Bullet.h"

constexpr unsigned int MAX_BULLETS = 10;

class Game
{
public:
	Game(int screenWidth, int screenHeight, const char* title);
	~Game();
	void run();

	void update();
	void draw();
	
private:
	int screenWidth;
	int screenHeight;
	const char* title;

	Player player;
	std::vector<Bullet> bullets;
};