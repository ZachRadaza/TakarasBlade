#include "Character.h"

Character::Character()
    : Entity(), radius(0.0f), health(0), accelaration(0.0f), velocity({ 0.0f, 0.0f }){}

Character::Character(
    Vector2 coords, 
    float width, 
    float height, 
    Texture2D *sprite,
    float speed, 
    float radius,
    int health, 
    float accelaration,
    Vector2 velocity
) : Entity(coords, width, height, sprite, speed), radius(radius), health(health), accelaration(accelaration), velocity(velocity){}

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

// getters

const float Character::getRadius() const { return this->radius; }

const int Character::getHealth() const { return this->health; }

const float Character::getAccelaration() const { return this->accelaration; }

const Vector2 Character::getVelocoty() const { return this->velocity; }

const bool Character::getHitsDash() const { return this->hitsDash; }

const Action Character::getCurrentAction(){ return this->currentAction; }

const float Character::getDashCooldown(){
    float cooldown = DASH_CD * -1;

    if(isDashing() || dashTimer < cooldown)
        return 0.0f;

    return dashTimer / cooldown;
}

const float Character::getParryCooldown(){
    float cooldown = PARRY_CD * -1;

    if(isDashing() || parryTimer < cooldown)
        return 0.0f;

    return parryTimer / cooldown;   
}

// setters

void Character::setRadius(float radius){ this->radius = radius; }

void Character::setHealth(int health){ this->health = health; }

void Character::adjustHealth(int addHealth){ this->health += addHealth; }

void Character::setVelocity(Vector2 velocity){ this->velocity = velocity; }

void Character::adjustVelocity(Vector2 adjust){ 
    this->velocity.x += adjust.x; 
    this->velocity.y += adjust.y;
}

void Character::setAccelaration(float accelaration){ this->accelaration = accelaration; }

void Character::setHitsDash(bool hitsDash){ this->hitsDash = hitsDash; }

// methods

const bool Character::isDead() const { return this->health <= 0; }

const bool Character::isDashing() const{ return dashTimer > 0.0f; }

const bool Character::isParrying() const{ return parryTimer > 0.0f; }

const bool Character::isStunned() const{ return stunTimer > 0.0f; }

void Character::updateTimers(){
    float downTime = GetFrameTime();

    this->dashTimer = dashTimer - downTime < -8.0f ? -8.0f : dashTimer - downTime;
    this->stunTimer = stunTimer - downTime < -8.0f ? -8.0f : stunTimer - downTime; 
    this->parryTimer = parryTimer - downTime < -8.0f ? -8.0f : parryTimer - downTime; 
}

Rectangle Character::getSpriteSource(){
    spriteSource = { 
        (float) (currentFrame * SPRITE_WIDTH),
        static_cast<float>(currentDirection) * SPRITE_WIDTH,
        SPRITE_WIDTH,
        SPRITE_WIDTH
    };

    updateAnimation();

    Action action = Action::RUN;

    if(velocity.x == 0.0f && velocity.y == 0.0f) action = Action::STANCE;
    
    if(isDashing()) action = Action::DASH;

    if(isStunned()) action = Action::STUN;

    if(isParrying()) action = Action::PARRY;
    
    if(isDead()) action = Action::DEAD;

    currentAction = action;

    return spriteSource;
}

void Character::dash(Vector2 adjust){
    if(isStunned() || isDead())
        return;

    float dashCooldown = DASH_CD * -1.0f;

    if(dashTimer > dashCooldown)
        return;

    Vector2 sign {
        velocity.x > 0.0f ? 1.0f : -1.0f, 
        velocity.y > 0.0f ? 1.0f : -1.0f
    };

    if(adjust.x != 0)
        velocity.x = std::abs(velocity.x * 2) > maxSpeed * 2
            ? velocity.x * 2
            : maxSpeed * sign.x * 2;

    if(adjust.y != 0)
        velocity.y = std::abs(velocity.y * 2) > maxSpeed * 2
            ? velocity.y * 2
            : maxSpeed * sign.y * 2;

    dashTimer = DASH_LENGTH;
}

void Character::parry(){
    float parryCooldown = PARRY_CD * -1.0f;

    if(parryTimer > parryCooldown)
        return;

    velocity.x = velocity.y = 0.0f;

    parryTimer = PARRY_LENGTH;
}

void Character::stun(){
    stunTimer = STUN_LENGTH;
}

void Character::adjustCoords(Vector2 adjust, float friction){
    float downTime = GetFrameTime();
    float drop = friction * downTime;

    if(isStunned() || isDead())
        adjust.x = adjust.y = 0;

    if(!isDashing())
        characterMovement(adjust, downTime, drop);

    if(!isParrying()){
        coords.x += velocity.x * downTime;
        coords.y += velocity.y * downTime;

        keepWithinScreen();
        currentDirection = findCurrentDirection(adjust);
    }

    updateTimers();
}

void Character::characterMovement(Vector2 adjust, float downTime, float drop){
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
}

void Character::keepWithinScreen(){
    if(coords.x < 0) 
        coords.x = 0;

    if(coords.y < 0) 
        coords.y = 0;

    if(coords.x + width > GetRenderWidth()) 
        coords.x = GetRenderWidth() - width;

    if(coords.y + height > GetRenderHeight()) 
        coords.y = GetRenderHeight() - height;
}