#pragma once
#include <raylib.h>
#include <vector>

#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"

constexpr unsigned int MAX_BULLETS = 10;

class Game
{
public:
	Game(int screenWidth, int screenHeight, const char* title);
	~Game();
	void run();

	void handleInput();
	void update();
	void draw();
	
private:
	void updateBullets();
	void updateAsteroids();
	
	void spawnAsteroid();
	void spawnBullet();

	void checkCollisions();

	void unloadTextures() const;

private:
	int screenWidth;
	int screenHeight;
	const char* title;

	Player player;
	std::vector<Bullet> bullets;
	std::vector<Asteroid> asteroids;

	float lastAsteroidSpawnTime = 0.0f;
	float asteroidSpawnInterval = 2.0f; // Spawn an asteroid every 2 seconds

	Texture2D asteroidTexture{};
};