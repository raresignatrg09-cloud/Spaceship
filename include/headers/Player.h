#pragma once

#include <raylib.h>

class Player
{
public:
	Player();
	~Player();

	void loadTexture(Vector2 position);
	void update(float dt);
	void draw() const;

    Vector2 getPostion() const { return position; }
    Vector2 getSize() const { return size; }

private:
    Texture2D playerTexture{};

    Vector2 position{};
    Vector2 size{};          // rendered sprite size
    Vector2 hitboxSize{};    // collision size
    Rectangle hitbox{};

    float scale = 0.1f;
    float hitboxScale = 0.7f;

    float speed = 350.0f;
    Vector2 velocity{};
};