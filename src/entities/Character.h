#pragma once
#include "./Entity.h"
#include <cmath>


class Character : public Entity{
private:
    int health;
    float accelaration;
    Vector2 velocity;

public:
    Character();
    Character(
        Vector2 coords, 
        float width, 
        float height, 
        Texture2D *sprite, 
        float speed, 
        int health, 
        float accelaration,
        Vector2 velocity
    );
    Character &operator=(const Character &other);
    ~Character();

    const int getHealth() const;
    void setHealth(int health);
    void adjustHealth(int addHealth);

    const Vector2 getVelocoty() const;
    void setVelocity(Vector2 velocity);
    void adjustVelocity(Vector2 adjust);

    const float getAccelaration() const;
    void setAccelaration(float accelaration);

    void adjustCoords(Vector2 adjust, float friction);
};