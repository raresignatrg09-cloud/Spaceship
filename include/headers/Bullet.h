#pragma once

#include <raylib.h>
#include "Hitbox.hpp"

class Bullet
{
public:
	Bullet() = default;
	Bullet(Vector2 position);
	void draw() const;
	void update();

	Vector2 getPosition() const { return position; }
	
	static constexpr float WIDTH = 10.0f;
	static constexpr float HEIGHT = 20.0f;

	Rectangle getHitbox() const { return hitbox.getHitbox(); }

private:
	Vector2 position{};
	Vector2 velocity{};

	float speed = 550.0f; // Speed of the bullet

	Hitbox hitbox{};
};