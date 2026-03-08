#include "Character.h"

Character::Character()
    : Entity(), health(0), accelaration(0), velocity({ 0, 0 }) {}

Character::Character(
    Vector2 coords, 
    float width, 
    float height, 
    Texture2D *sprite,
    float speed, 
    int health, 
    float accelaration,
    Vector2 velocity
) : Entity(coords, width, height, sprite, speed), health(health), accelaration(accelaration), velocity(velocity){}

Character &Character::operator=(const Character &other){
    coords = other.coords;
    width = other.width;
    height = other.height;
    health = other.health;
    sprite = other.sprite;
    maxSpeed = other.maxSpeed;
    accelaration = other.accelaration;
    velocity = other.velocity;

    return *this;
}

Character::~Character(){}

const int Character::getHealth() const { return this->health; }

const float Character::getAccelaration() const { return this->accelaration; }

const Vector2 Character::getVelocoty() const { return this->velocity; }

void Character::setHealth(int health){ this->health = health; }

void Character::adjustHealth(int addHealth){ this->health += addHealth; }

void Character::setVelocity(Vector2 velocity){ this->velocity = velocity; }

void Character::adjustVelocity(Vector2 adjust){ 
    this->velocity.x += adjust.x; 
    this->velocity.y += adjust.y;
}

void Character::setAccelaration(float accelaration){ this->accelaration = accelaration; }

void Character::adjustCoords(Vector2 adjust, float friction){
    float downTime = GetFrameTime();
    float drop = friction * downTime;

    if(adjust.x != 0.0f){
        if((adjust.x * velocity.x) < 0.0f)
            velocity.x = 0.0f;

        velocity.x += adjust.x * accelaration * downTime;
    } else {
        float speed = std::fabs(velocity.x);
        float newSpeed = speed - drop > 0.0f ? speed - drop : 0.0f;

        if(speed > 0.0f)
            velocity.x *= newSpeed / speed;
    }

    if(adjust.y != 0.0f){
        if((adjust.y * velocity.y) < 0.0f)
            velocity.y = 0.0f;

        velocity.y += adjust.y * accelaration * downTime;
    } else {
        float speed = std::fabs(velocity.y);
        float newSpeed = speed - drop > 0.0f ? speed - drop : 0.0f;

        if(speed > 0.0f)
            velocity.y *= newSpeed / speed;
    }

    float speedSq = (velocity.x * velocity.x) + (velocity.y * velocity.y);
    float maxSpeedSq = maxSpeed * maxSpeed;

    if(speedSq > maxSpeedSq){
        float speed = std::sqrt(speedSq);
        velocity.x = (velocity.x / speed) * maxSpeed;
        velocity.y = (velocity.y / speed) * maxSpeed;
    }

    coords.x += velocity.x * downTime;
    coords.y += velocity.y * downTime;
}