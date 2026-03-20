#include "Visual.h"

Visual::Visual()
    : takaraSprites(), background(), elementSprites(), uiSprites() {}

Visual::~Visual(){
    for(Texture2D &texture : takaraSprites)
        UnloadTexture(texture);

    for(Texture2D &texture: elementSprites)
        UnloadTexture(texture);

    for(Texture2D &texture : uiSprites)
        UnloadTexture(texture);
    
    UnloadTexture(background);
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

void Visual::initElementTextures(){
    elementSprites[static_cast<int>(Elements::BLOOD)] = LoadTexture(ELEMENT_BLOOD);
    elementSprites[static_cast<int>(Elements::SMOKE)] = LoadTexture(ELEMENT_SMOKE);
    elementSprites[static_cast<int>(Elements::SPARK)] = LoadTexture(ELEMENT_SPARK);
}

void Visual::initUiTextures(){
    uiSprites[static_cast<int>(UI::HEALTH)] = LoadTexture(UI_HEALTH);
    uiSprites[static_cast<int>(UI::WAVE)] = LoadTexture(UI_WAVE);
    uiSprites[static_cast<int>(UI::KILLS)] = LoadTexture(UI_KILLS);
    uiSprites[static_cast<int>(UI::DASH)] = LoadTexture(UI_DASH);
    uiSprites[static_cast<int>(UI::PARRY)] = LoadTexture(UI_PARRY);
    uiSprites[static_cast<int>(UI::PAUSE)] = LoadTexture(UI_PAUSE);
}

void Visual::initBackground(){
    background = LoadTexture(GRASS);

    SetTextureFilter(background, TEXTURE_FILTER_POINT);
    SetTextureWrap(background, TEXTURE_WRAP_REPEAT);
}

// public

void Visual::initTextures(){
    initTakaraTextures();
    initElementTextures();
    initUiTextures();
    initBackground();
}

Texture2D *Visual::getTakaraSprite(int index){
    if(!(index >= 0 && index <= static_cast<int>(Action::COUNT)))
        return nullptr;

    return &takaraSprites[index];
}

Texture2D *Visual::getElementSprite(int index){
    if(!(index >= 0 && index <= static_cast<int>(Elements::COUNT)))
        return nullptr;

    return &elementSprites[index];
}

Texture2D *Visual::getBackground(){
    return &background;
}

Texture2D *Visual::getUISprite(int index){
    if(!(index >= 0 && index <= static_cast<int>(UI::COUNT)))
        return nullptr;

    return &uiSprites[index];
}