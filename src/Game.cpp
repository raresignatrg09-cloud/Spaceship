#include "headers/Game.h"

Game::Game(int screenWidth, int screenHeight, const char* title)
	: screenWidth(screenWidth), screenHeight(screenHeight), title(title)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(screenWidth, screenHeight, title);
	SetTargetFPS(60);

	player.initPlayer({ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f });

	asteroidTexture   = LoadTexture(RESOURCES_PATH "sprites/Asteroid.png");
	backgroundTexture = LoadTexture(RESOURCES_PATH "sprites/background.png");
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
		handleInput();
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
	if (IsKeyPressed(KEY_R) && gameOver)
	{
		gameOver = false;
		player.reset({ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f });
		asteroids.clear(); // Clear existing asteroids
		bullets.clear();   // Clear existing bullets
	}
	if (IsKeyPressed(KEY_F11))
	{
		ToggleFullscreen();

		player.initPlayer({ GetScreenWidth() / 2.0f,GetScreenHeight() / 2.0f });
	}
}

void Game::update()
{
	if (player.getHealth() <= 0)
	{
		gameOver = true;
		TraceLog(LOG_INFO, "Game Over!");
		return;
	}
	
	if (!gameOver)
	{
		player.update(GetFrameTime());
		updateBullets();
		updateAsteroids();

		checkCollisions();
	}
}

void Game::draw()
{
	BeginDrawing();
		ClearBackground(BLACK);

		DrawTexturePro(
			backgroundTexture,{
				0,0,
				static_cast<float>(backgroundTexture.width),
				static_cast<float>(backgroundTexture.height)},
			{0.f,0.f,static_cast<float>(GetScreenWidth()),static_cast<float>(GetScreenHeight())},
			{0.0f,0.0f},
			0.0f,
			WHITE
		);

		for (auto& bullet : bullets)
			bullet.draw();

		for (auto& asteroid : asteroids)
			asteroid.draw();

		player.draw();

		DrawText(TextFormat("Health: %d", player.getHealth()), 10, 10, 20, GREEN);

		if (gameOver)
		{
			const char* gameOverText = "Game Over!";
			const char* restartText = "Press R to restart.";

			DrawText(
				gameOverText,
				GetScreenWidth() / 2 - MeasureText(gameOverText, 50) / 2,
				GetScreenHeight() / 2 - 40,
				50,
				RED
			);

			DrawText(
				restartText,
				GetScreenWidth() / 2 - MeasureText(restartText, 20) / 2,
				GetScreenHeight() / 2 + 20,
				20,
				WHITE
			);
		}

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
			player.takeDamage(5);

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
	Vector2 spawnPosition = { (float)GetRandomValue(Asteroid::getRadius(), GetScreenWidth() - Asteroid::getRadius()), 0.0f};

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
	for (auto asteroidIt = asteroids.begin(); asteroidIt != asteroids.end();)
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

				if (GetRandomValue(0, 10) == 0)
				{
					TraceLog(LOG_INFO, "Player healed by asteroid!");
					player.heal(15);
				}

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

	if (backgroundTexture.id != 0)
		UnloadTexture(backgroundTexture);
}
