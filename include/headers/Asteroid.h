#pragma once

#include <raylib.h>
#include "Hitbox.hpp"

class Asteroid
{
public:
	Asteroid(Vector2 position,Texture2D texture);

	void update();
	void draw() const;

	Vector2 getPosition() const { return position; }
	
	static constexpr float getRadius() { return 50.0f; } // Radius of the asteroid

	Rectangle getHitbox() const { return hitbox.getHitbox(); }
		
private:
	Vector2 position{};
	Vector2 velocity{};
	Vector2 size{};

	float speed = 150.0f; // Speed of the asteroid
	float scale = 4.f;
	float hitboxScale = 0.7f;

	Hitbox hitbox{};

	Texture2D texture;
};