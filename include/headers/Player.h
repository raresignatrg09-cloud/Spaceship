#pragma once

#include <raylib.h>
#include "Hitbox.hpp"

class Player
{
public:
	Player();
	~Player();

    void initPlayer(Vector2 position);
	void update(float dt);
	void draw() const;

    Vector2 getPostion() const { return position; }
    Vector2 getSize() const { return size; }

    void takeDamage(int damage);
    void heal(int amount);
    int getHealth() const { return health; }

	Rectangle getHitbox() const { return hitbox.getHitbox(); }

    void reset(Vector2 position);

private:
    Texture2D playerTexture{};

    Vector2 position{};
    Vector2 size{};          // rendered sprite size

    float scale = 0.1f;
    float hitboxScale = 0.7f;

    float speed = 350.0f;
    Vector2 velocity{};

	int health = 10.;

    Hitbox hitbox{};
};