#pragma once
#include "raylib.h"

class Entity{
protected:
    Vector2 coords;
    float width, height;
    Texture2D *sprite;
    float maxSpeed;

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

    void setCoords(Vector2 coords);
    void setWidth(float width);
    void setHeight(float height);
    void setSprite(Texture2D *sprite);
    void setMaxSpeed(float maxSpeed);

    void adjustCoords(Vector2 adjust);
};