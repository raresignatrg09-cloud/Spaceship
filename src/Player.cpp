#include "headers/Player.h"
#include <raymath.h>
#include <algorithm>

Player::Player() = default;

Player::~Player()
{
	if (playerTexture.id != 0)
		UnloadTexture(playerTexture);
}

void Player::initPlayer(Vector2 position)
{
	this->position = position;

	const char* path = RESOURCES_PATH "sprites/playerTexture.png";

	playerTexture = LoadTexture(path);

	// Actual size on screen
	size = {
		playerTexture.width * scale,
		playerTexture.height * scale
	};

	hitbox.setSize(size, hitboxScale);
	hitbox.setPosition(position, size);
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

	position = Vector2Add(
		position,
		Vector2Scale(velocity, dt)
	);

	hitbox.setPosition(position, size);
	
	// Get current hitbox
	Rectangle rect = hitbox.getHitbox();

	// Keep player inside screen
	if (rect.x < 0)
		position.x -= rect.x;

	if (rect.x + rect.width > GetScreenWidth())
		position.x -= (rect.x + rect.width) - GetScreenWidth();

	if (rect.y < 0)
		position.y -= rect.y;

	if (rect.y + rect.height > GetScreenHeight())
		position.y -= (rect.y + rect.height) - GetScreenHeight();

	// Update hitbox again after correcting position
	hitbox.setPosition(position, size);
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
	hitbox.drawHitbox();
}

void Player::takeDamage(int damage)
{
	health = std::clamp(health-damage,0,100);
}

void Player::heal(int amount)
{
	health = std::clamp(health + amount, 0, 100);
}
