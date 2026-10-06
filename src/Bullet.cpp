#include "headers/Bullet.h"
#include <raymath.h>

Bullet::Bullet(Vector2 position)
	:position(position)
{
	hitbox.setSize({WIDTH, HEIGHT}, 1.0f);
	hitbox.setPosition(position, {WIDTH, HEIGHT});
}

void Bullet::update()
{
	velocity = { 0,-speed };

	float dt = GetFrameTime();

	position = Vector2Add(
		position,
		Vector2Scale(velocity, dt)
	);

	hitbox.setPosition(position, { WIDTH, HEIGHT });
}

void Bullet::draw() const
{
	DrawRectangleV(position, {WIDTH,HEIGHT}, YELLOW);

#ifdef _DEBUG
	hitbox.drawHitbox();
#endif
}