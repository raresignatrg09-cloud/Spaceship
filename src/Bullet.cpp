#include "headers/Bullet.h"

Bullet::Bullet(Vector2 position)
	:position(position)
{
}

void Bullet::draw() const
{
	DrawRectangleV(position, {WIDTH,HEIGHT}, YELLOW);
}

void Bullet::update()
{
	position.y -= 15;
}