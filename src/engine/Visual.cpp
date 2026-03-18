#include "Visual.h"

Visual::Visual()
    : takaraSprites() {}

Visual::~Visual(){
    for(Texture2D &texture : takaraSprites)
        UnloadTexture(texture);

    
}

// private

void Visual::initTakaraTextures(){
    takaraSprites[static_cast<int>(Action::STANCE)] = LoadTexture(TAKARA_STANCE);
    takaraSprites[static_cast<int>(Action::RUN)] = LoadTexture(TAKARA_RUN);
    takaraSprites[static_cast<int>(Action::DASH)] = LoadTexture(TAKARA_DASH);
    takaraSprites[static_cast<int>(Action::PARRY)] = LoadTexture(TAKARA_PARRY);
    takaraSprites[static_cast<int>(Action::STUN)] = LoadTexture(TAKARA_STUN);
    takaraSprites[static_cast<int>(Action::DEAD)] = LoadTexture(TAKARA_DEAD);
}

// public

void Visual::initTextures(){
    initTakaraTextures();

}

Texture2D *Visual::getTakaraSprite(int index){
    if(!(index >= 0 && index <= static_cast<int>(Action::COUNT)))
        return nullptr;

    return &takaraSprites[index];
}