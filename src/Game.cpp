#include "headers/Game.h"

Game::Game(int screenWidth, int screenHeight, const char* title)
	: screenWidth(screenWidth), screenHeight(screenHeight), title(title)
{
	InitWindow(screenWidth, screenHeight, title);
	SetTargetFPS(60);

	player.loadTexture({ screenWidth / 2.0f, screenHeight / 2.0f });
}

Game::~Game()
{
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

void Game::update()
{
	if (IsKeyDown(KEY_ESCAPE))
	{
		CloseWindow();
	}
	if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		TraceLog(LOG_INFO, "Pressed!\n");

		Vector2 playerPos  = player.getPostion();
		Vector2 playerSize = player.getSize();
		Vector2 bulletSize = { Bullet::WIDTH,Bullet::HEIGHT };

		Vector2 spawnPosition = {
			playerPos.x + (playerSize.x - bulletSize.x) / 2.0f,
			playerPos.y - bulletSize.y
		};

		if (bullets.size() < MAX_BULLETS)
			bullets.push_back(Bullet(spawnPosition));
	}

	player.update(GetFrameTime());

	for(auto it=bullets.begin();it!=bullets.end();)
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

void Game::draw()
{
	BeginDrawing();
		ClearBackground(BLACK);

		for (auto& bullet : bullets)
			bullet.draw();

		player.draw();

	EndDrawing();
}
