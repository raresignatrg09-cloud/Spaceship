#include "headers/Game.h"

Game::Game(int screenWidth, int screenHeight, const char* title)
	: screenWidth(screenWidth), screenHeight(screenHeight), title(title)
{
	InitWindow(screenWidth, screenHeight, title);
	SetTargetFPS(60);

	player.initPlayer({ screenWidth / 2.0f, screenHeight / 2.0f });

	asteroidTexture = LoadTexture(RESOURCES_PATH "sprites/Asteroid.png");
}

Game::~Game()
{
	unloadTextures();
	CloseWindow();
}

void Game::run()
{
	while (!WindowShouldClose())
	{
		update();
		draw();
	}
}

void Game::handleInput()
{
	if (IsKeyDown(KEY_ESCAPE))
	{
		CloseWindow();
	}
	if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		spawnBullet();
	}
}

void Game::update()
{
	handleInput();

	player.update(GetFrameTime());
	updateBullets();
	updateAsteroids();

	checkCollisions();
}

void Game::draw()
{
	BeginDrawing();
		ClearBackground(BLACK);

		for (auto& bullet : bullets)
			bullet.draw();

		for (auto& asteroid : asteroids)
			asteroid.draw();

		player.draw();

		DrawText(TextFormat("Health: %d", player.getHealth()), 10, 10, 20, GREEN);

	EndDrawing();
}

void Game::updateBullets()
{
	for (auto it = bullets.begin(); it != bullets.end();)
	{
		it->update();

		if (it->getPosition().y < 0)
		{
			TraceLog(LOG_INFO, "ERASING BULLET - size before: %zu", bullets.size());

			it = bullets.erase(it);

			TraceLog(LOG_INFO, "size after: %zu", bullets.size());
		}
		else
		{
			++it;
		}
	}
}

void Game::updateAsteroids()
{
	float currentTime = GetTime();

	if (currentTime - lastAsteroidSpawnTime >= asteroidSpawnInterval)
	{
		spawnAsteroid();
		lastAsteroidSpawnTime = currentTime;
	}

	for (auto it = asteroids.begin(); it != asteroids.end();)
	{
		it->update();

		if (it->getPosition().y > GetScreenHeight())
		{
			TraceLog(LOG_INFO, "ERASING ASTEROID - size before: %zu", asteroids.size());

			it = asteroids.erase(it);

			TraceLog(LOG_INFO, "size after: %zu", asteroids.size());
		}
		else
		{
			++it;
		}
	}
}

void Game::spawnAsteroid()
{
	Vector2 spawnPosition = { (float)GetRandomValue(Asteroid::getRadius(), screenWidth - Asteroid::getRadius()), 0.0f};

	asteroids.emplace_back(spawnPosition, asteroidTexture);
}

void Game::spawnBullet()
{
	Vector2 playerPos = player.getPostion();
	Vector2 playerSize = player.getSize();
	Vector2 bulletSize = { Bullet::WIDTH,Bullet::HEIGHT };

	Vector2 spawnPosition = {
		playerPos.x + (playerSize.x - bulletSize.x) / 2.0f,
		playerPos.y - bulletSize.y
	};

	if (bullets.size() < MAX_BULLETS)
		bullets.push_back(Bullet(spawnPosition));
}

void Game::checkCollisions()
{
	for (auto asteroidIt=asteroids.begin();asteroidIt!=asteroids.end();)
	{
		if (CheckCollisionRecs(player.getHitbox(), asteroidIt->getHitbox()))
		{
			TraceLog(LOG_INFO, "Player hit by asteroid!");
			player.takeDamage(10);
			asteroidIt = asteroids.erase(asteroidIt);

			continue;
		}

		bool asteroidDestroyed = false;

		for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();)
		{
			if (CheckCollisionRecs(bulletIt->getHitbox(), asteroidIt->getHitbox()))
			{
				TraceLog(LOG_INFO, "Bullet hit asteroid!");

				asteroidIt = asteroids.erase(asteroidIt);
				bulletIt = bullets.erase(bulletIt);

				asteroidDestroyed = true;
				break;
			}

			++bulletIt;
		}

		if (!asteroidDestroyed)
		{
			++asteroidIt;
		}
	}
}

void Game::unloadTextures() const
{
	if (asteroidTexture.id != 0)
		UnloadTexture(asteroidTexture);
}
