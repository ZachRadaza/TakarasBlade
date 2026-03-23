#include "Visual.h"

Visual::Visual()
    : takaraSprites(), enemySprites(), background(), elementSprites(), uiSprites() {}

Visual::~Visual(){
    for(Texture2D &texture : takaraSprites)
        UnloadTexture(texture);

    for(Texture2D &texture : enemySprites)
        UnloadTexture(texture);

    for(Texture2D &texture: elementSprites)
        UnloadTexture(texture);

    for(Texture2D &texture : uiSprites)
        UnloadTexture(texture);
    
    for(Texture2D &texture : background)
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

void Visual::initEnemyTextures(){
    enemySprites[static_cast<int>(Action::STANCE)] = LoadTexture(ENEMY_STANCE);
    enemySprites[static_cast<int>(Action::RUN)] = LoadTexture(ENEMY_RUN);
    enemySprites[static_cast<int>(Action::DASH)] = LoadTexture(ENEMY_DASH);
    enemySprites[static_cast<int>(Action::PARRY)] = LoadTexture(ENEMY_PARRY);
    enemySprites[static_cast<int>(Action::STUN)] = LoadTexture(ENEMY_STUN);
    enemySprites[static_cast<int>(Action::DEAD)] = LoadTexture(ENEMY_DEAD);
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
    uiSprites[static_cast<int>(UI::BUTTON)] = LoadTexture(UI_BUTTON);
}

void Visual::initBackground(){
    background[static_cast<int>(PageType::HOME)] = LoadTexture(GRASS_DETAILED);
    background[static_cast<int>(PageType::PLAY)] = LoadTexture(GRASS);

    for(Texture2D &texture : background){
        SetTextureFilter(texture, TEXTURE_FILTER_POINT);
        SetTextureWrap(texture, TEXTURE_WRAP_REPEAT);
    }
}

// public

void Visual::initTextures(){
    initTakaraTextures();
    initEnemyTextures();
    initElementTextures();
    initUiTextures();
    initBackground();
}

Texture2D *Visual::getTakaraSprite(Action index){
    return &takaraSprites[static_cast<int>(index)];
}

Texture2D *Visual::getEnemySprite(Action index){
    return &enemySprites[static_cast<int>(index)];
}

Texture2D *Visual::getElementSprite(Elements index){
    return &elementSprites[static_cast<int>(index)];
}

Texture2D *Visual::getBackground(PageType index){
    return &background[static_cast<int>(index)];
}

Texture2D *Visual::getUISprite(UI index){
    return &uiSprites[static_cast<int>(index)];
}