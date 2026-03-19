#pragma once
#include "raylib.h"
#include "../engine/Enums.h"

class Entity{
protected:
    static constexpr float SPRITE_WIDTH = 32.0f;
    static constexpr float ANIMATION_LENGTH = 0.15f;
    static constexpr int NUM_FRAMES = 4;

    Vector2 coords;
    float width, height;
    Texture2D *sprite;
    float maxSpeed;

    int currentFrame = 1;
    float frameTimer = 0.0f;
    bool animatedOnce = false;
    Direction currentDirection = Direction::DOWN;
    Rectangle spriteSource;

    Direction findCurrentDirection(Vector2 adjust);
    void updateAnimation();

public:
    Entity();
    Entity(Vector2 coords, float width, float height, Texture2D *sprite, float maxSpeed);
    Entity &operator=(const Entity &other);
    virtual ~Entity();

    const Vector2 getCoords() const;
    const float getWidth() const;
    const float getHeight() const;
    Texture2D *getSprite();
    const float getMaxSpeed() const;
    virtual Rectangle getSpriteSource();
    const Direction getCurrentDirection();
    const bool getAnimatedOnce();

    void setCoords(Vector2 coords);
    void setWidth(float width);
    void setHeight(float height);
    void setSprite(Texture2D *sprite);
    void setMaxSpeed(float maxSpeed);
    void setCurrentDirection(Direction direction);

    void adjustCoords(Vector2 adjust);
};