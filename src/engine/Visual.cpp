#include "Visual.h"

Visual::Visual()
    : sprites() {}

Visual::~Visual(){
    for(Texture2D &texture : sprites)
        UnloadTexture(texture);
}

void Visual::initTextures(){
    sprites[static_cast<int>(TexSprite::TAKARA)] = LoadTexture(VisualFiles::TAKARA_FILE);
}

Texture2D *Visual::getSprite(int index){
    if(!(index >= 0 && index <= static_cast<int>(TexSprite::COUNT)))
        return nullptr;

    return &sprites[index];
}