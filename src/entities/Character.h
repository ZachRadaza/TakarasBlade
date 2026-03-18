#pragma once
#include "./Entity.h"
#include "../engine/Visual.h"
#include "../engine/Action.h"
#include <cmath>


class Character : public Entity{
private:
    static constexpr float DASH_LENGTH = 0.3f;
    static constexpr float DASH_CD = 0.6f;
    static constexpr float PARRY_LENGTH = 0.4f;
    static constexpr float PARRY_CD = 0.5f;
    static constexpr float STUN_LENGTH = 5.0f;

    int health;
    float accelaration;
    Vector2 velocity;
    float radius;

    float dashTimer = 0.0f;
    float parryTimer = 0.0f;
    float stunTimer = 0.0f;
    bool hitsDash = false;
    Action currentAction = Action::STANCE;

    void characterMovement(Vector2 adjust, float downTime, float drop);
    void keepWithinScreen();

    void updateTimers();
public:
    Character();
    Character(
        Vector2 coords, 
        float width, 
        float height, 
        Texture2D *sprite, 
        float speed, 
        float radius,
        int health, 
        float accelaration,
        Vector2 velocity
    );
    Character &operator=(const Character &other);
    ~Character();

    Rectangle getSpriteSource() override;

    const Action getCurrentAction();

    const float getRadius() const;
    void setRadius(float radius);

    const bool isDead() const;
    const int getHealth() const;
    void setHealth(int health);
    void adjustHealth(int addHealth);

    const Vector2 getVelocoty() const;
    void setVelocity(Vector2 velocity);
    void adjustVelocity(Vector2 adjust);

    const float getAccelaration() const;
    void setAccelaration(float accelaration);

    void adjustCoords(Vector2 adjust, float friction);

    void dash(Vector2 adjust);
    const bool isDashing() const;
    const bool getHitsDash() const;
    void setHitsDash(bool hitDash);

    void parry();
    const bool isParrying() const;

    void stun();
    const bool isStunned() const;
};