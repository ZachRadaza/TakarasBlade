#include "PlayPage.h"
#include "raylib.h"

Play::Play()
    : Page(), player({ 0, 0 }, 20.0f, 20.0f, nullptr, TAKARA_SPEED, 100, TAKARA_ACCELARATION, { 0, 0 }) {}

Play::Play(Audio *audioEngine, Visual *visualEngine)
    : Page(audioEngine, visualEngine), 
    player(
        { 0, 0 }, 
        20.0f, 
        20.0f, 
        visualEngine->getSprite(static_cast<int>(Visual::TexSprite::TAKARA)), 
        TAKARA_SPEED,
        100, 
        TAKARA_ACCELARATION,
        { 0, 0 }
    )
{
    
}

Play::~Play(){

}

// Private
void Play::handleInput(){
    float x, y;
    x = y = 0;

    if(IsKeyDown(KEY_W))
        y -= 1;

    if(IsKeyDown(KEY_A))
        x -= 1;

    if(IsKeyDown(KEY_S))
        y += 1;

    if(IsKeyDown(KEY_D))
        x += 1;

    this->player.adjustCoords({ x, y }, TAKARA_ACCELARATION);
}


// Public

void Play::update(){
    handleInput();


}

void Play::draw(){
    ClearBackground(RAYWHITE);

    DrawTextureEx(*player.getSprite(), player.getCoords(), 0, 1, WHITE);

    DrawText(TextFormat("Width: %d", GetScreenWidth()), 20, 20, 20, BLACK);

}

void Play::setAudioEngine(Audio *audioEngine){ 
    this->audioEngine = audioEngine; 
}

void Play::setVisualEngine(Visual *visualEngine){ 
    this->visualEngine = visualEngine; 
    player.setSprite(
        visualEngine->getSprite(static_cast<int>(Visual::TexSprite::TAKARA))
    );
}