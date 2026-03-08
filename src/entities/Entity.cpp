#include "Entity.h"

Entity::Entity()
    : coords({ 0, 0 }), width(0), height(0), sprite(nullptr), maxSpeed(0) {}

Entity::Entity(Vector2 coords, float width, float height, Texture2D *sprite, float maxSpeed) 
    : coords(coords), width(width), height(height), sprite(sprite), maxSpeed(maxSpeed) {}

Entity &Entity::operator=(const Entity &other){
    coords = other.coords;
    width = other.width;
    height = other.height;
    sprite = other.sprite;
    maxSpeed = other.maxSpeed;
    return *this;
}

Entity::~Entity(){
}

const Vector2 Entity::getCoords() const{ return this->coords; }

const float Entity::getWidth() const{ return this->width; }

const float Entity::getHeight() const{ return this->height; }

Texture2D *Entity::getSprite(){ return this->sprite; }

const float Entity::getMaxSpeed() const{ return this->maxSpeed; }

void Entity::setCoords(Vector2 coords){ this->coords = coords; }

void Entity::setWidth(float width){ this->width = width; }

void Entity::setHeight(float height){ this->height = height; }

void Entity::setSprite(Texture2D *sprite){ this->sprite = sprite; }

void Entity::setMaxSpeed(float speed){ this->maxSpeed = speed; }

void Entity::adjustCoords(Vector2 adjust){
    float downTime = GetFrameTime();

    coords.x += maxSpeed * downTime * adjust.x;
    coords.y += maxSpeed * downTime * adjust.y;
}