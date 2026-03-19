#include "Entity.h"

Entity::Entity()
    : coords({ 0, 0 }), width(0), height(0), sprite(nullptr), maxSpeed(0) {}

Entity::Entity(Vector2 coords, float width, float height, Texture2D *sprite, float maxSpeed) 
    : coords(coords), width(width), height(height), sprite(sprite), maxSpeed(maxSpeed) {}

Entity &Entity::operator=(const Entity &other){
    this->coords = other.coords;
    this->width = other.width;
    this->height = other.height;
    this->sprite = other.sprite;
    this->maxSpeed = other.maxSpeed;
    return *this;
}

Entity::~Entity(){
}

Direction Entity::findCurrentDirection(Vector2 adjust){
    Direction current = currentDirection;

    if(adjust.x > 0)
        current = Direction::RIGHT;
    else if(adjust.x < 0)
        current = Direction::LEFT;

    if(adjust.y > 0)
        current = Direction::DOWN;
    else if(adjust.y < 0)
        current = Direction::TOP;

    return current;
}

void Entity::updateAnimation(){
    float downTime = GetFrameTime();
    
    frameTimer -= downTime;
    if(frameTimer <= 0.0f){
        currentFrame = currentFrame + 1 < NUM_FRAMES
            ? currentFrame + 1
            : 0;

        animatedOnce = true;
        frameTimer = ANIMATION_LENGTH;
    }
}

const Vector2 Entity::getCoords() const{ return this->coords; }

const float Entity::getWidth() const{ return this->width; }

const float Entity::getHeight() const{ return this->height; }

Texture2D *Entity::getSprite(){ return this->sprite; }

const float Entity::getMaxSpeed() const{ return this->maxSpeed; }

Rectangle Entity::getSpriteSource(){
    spriteSource = { 
        (float) (currentFrame * SPRITE_WIDTH),
        static_cast<float>(currentDirection) * SPRITE_WIDTH,
        SPRITE_WIDTH,
        SPRITE_WIDTH
    };

    updateAnimation();

    return spriteSource;
}

const Direction Entity::getCurrentDirection(){ return this->currentDirection; }

const bool Entity::getAnimatedOnce(){ return this->animatedOnce; }

void Entity::setCoords(Vector2 coords){ this->coords = coords; }

void Entity::setWidth(float width){ this->width = width; }

void Entity::setHeight(float height){ this->height = height; }

void Entity::setSprite(Texture2D *sprite){ 
    this->sprite = sprite; 

    this->currentFrame = 1;
    this->frameTimer = 0.0f;
}

void Entity::setMaxSpeed(float speed){ this->maxSpeed = speed; }

void Entity::setCurrentDirection(Direction direction){ this->currentDirection = direction; }

void Entity::adjustCoords(Vector2 adjust){
    float downTime = GetFrameTime();

    currentDirection = findCurrentDirection(adjust);

    coords.x += maxSpeed * downTime * adjust.x;
    coords.y += maxSpeed * downTime * adjust.y;
}