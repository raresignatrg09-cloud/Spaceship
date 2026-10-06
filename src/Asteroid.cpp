#include "headers/Asteroid.h"
#include <raymath.h>

Asteroid::Asteroid(Vector2 position, Texture2D texture)
	:position(position),texture(texture)
{
	size = {
		texture.width * scale,
		texture.height * scale
	};

	hitbox.setSize(size, hitboxScale);
	hitbox.setPosition({ position.x - size.x / 2.0f,position.y - size.y / 2.0f }, size);
}

void Asteroid::update()
{
	velocity = { 0, speed };

	float dt = GetFrameTime();

	position = Vector2Add(
		position,
		Vector2Scale(velocity, dt)
	);

	hitbox.setPosition({ position.x - size.x / 2.0f,position.y - size.y / 2.0f }, size);
}

void Asteroid::draw() const
{
	DrawTexturePro(
		texture,
		{
			0,
			0,
			static_cast<float>(texture.width),
			static_cast<float>(texture.height)
		},
	{
		position.x,
		position.y,
		size.x,
		size.y
	},
	{
		size.x / 2.0f,
		size.y / 2.0f
	},
		0.0f,
		WHITE
	);

#ifdef _DEBUG
	hitbox.drawHitbox();
#endif
}