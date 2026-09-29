#include "headers/Player.h"
#include <raymath.h>

Player::Player() = default;

Player::~Player()
{
	if (playerTexture.id != 0)
		UnloadTexture(playerTexture);
}

void Player::loadTexture(Vector2 position)
{
	this->position = position;

	const char* path = RESOURCES_PATH "sprites/playerTexture.png";

	playerTexture = LoadTexture(path);

	// Actual size on screen
	size = {
		playerTexture.width * scale,
		playerTexture.height * scale
	};

	// Hitbox is 70% of the sprite
	hitboxSize = {
		size.x * hitboxScale,
		size.y * hitboxScale
	};

	hitbox = {
		position.x + (size.x - hitboxSize.x) / 2.0f,
		position.y + (size.y - hitboxSize.y) / 2.0f,
		hitboxSize.x,
		hitboxSize.y
	};
}

void Player::update(float dt)
{
	velocity = { 0, 0 };

	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
		velocity.y -= 1;

	if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
		velocity.y += 1;

	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
		velocity.x -= 1;

	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
		velocity.x += 1;

	if (Vector2Length(velocity) > 0)
		velocity = Vector2Normalize(velocity);

	velocity = Vector2Scale(velocity, speed);

	// Move player
	position = Vector2Add(
		position,
		Vector2Scale(velocity, dt)
	);

	// Hitbox offset inside sprite
	float offsetX = (size.x - hitbox.width) / 2.0f;
	float offsetY = (size.y - hitbox.height) / 2.0f;

	// Update hitbox BEFORE checking collision
	hitbox.x = position.x + offsetX;
	hitbox.y = position.y + offsetY;

	// Keep hitbox inside screen
	if (hitbox.x < 0)
		position.x -= hitbox.x;

	if (hitbox.x + hitbox.width > GetScreenWidth())
		position.x -= (hitbox.x + hitbox.width) - GetScreenWidth();

	if (hitbox.y < 0)
		position.y -= hitbox.y;

	if (hitbox.y + hitbox.height > GetScreenHeight())
		position.y -= (hitbox.y + hitbox.height) - GetScreenHeight();

	// Update hitbox one final time after correction
	hitbox.x = position.x + offsetX;
	hitbox.y = position.y + offsetY;
}

void Player::draw() const
{
	DrawTexturePro(
		playerTexture,

		// Entire texture
		{
			0,
			0,
			static_cast<float>(playerTexture.width),
			static_cast<float>(playerTexture.height)
		},

		// Scaled sprite
		{
			position.x,
			position.y,
			size.x,
			size.y
		},

		{ 0, 0 },
		0.0f,
		WHITE
	);

	// Debug hitbox
	DrawRectangleLinesEx(hitbox, 2.0f, RED);
}