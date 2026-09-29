#pragma once

#include <raylib.h>

class Bullet
{
public:
	Bullet() = default;
	Bullet(Vector2 position);
	void draw() const;
	void update();

	Vector2 getPosition()const { return position; }
	
	static constexpr float WIDTH = 10.0f;
	static constexpr float HEIGHT = 20.0f;

private:
	Vector2 position;
};