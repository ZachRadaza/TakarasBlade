#include "HomePage.h"

Home::Home()
    : Page(), 
    playButton(
        {
            static_cast<float>((GetRenderWidth() / 2) - BUTTON_WIDTH / 2),
            static_cast<float>((GetRenderHeight() / 2)  - BUTTON_HEIGHT / 2)
        },
        BUTTON_WIDTH,
        BUTTON_HEIGHT,
        nullptr,
        0.0f
    ) 
{}

Home::Home(Audio *audioEngine, Visual *visualEngine)
    :Page(audioEngine, visualEngine),
    playButton(
        {
            static_cast<float>((GetRenderWidth() / 2) - BUTTON_WIDTH / 2),
            static_cast<float>(GetRenderHeight() / 2)
        },
        BUTTON_WIDTH,
        BUTTON_HEIGHT,
        visualEngine->getUISprite(UI::BUTTON),
        0.0f
    ) 
{}

Home::~Home() {}

void Home::update(){
    handleInput();

    if(!audioEngine->isHomeMusicPlaying())
        audioEngine->playHomeMusic();

    audioEngine->updateHomeMusic();
}

void Home::drawBackground(){
    float screenWidth = static_cast<float>(GetRenderWidth());
    float screenHeight = static_cast<float>(GetRenderHeight());
    float scale = 4.0f;

    Rectangle source = { 0, 0, screenWidth / scale, screenHeight / scale };
    Rectangle dest = { 0, 0, screenWidth, screenHeight };
    
    DrawTexturePro(
        *visualEngine->getBackground(PageType::HOME),
        source,
        dest,
        { 0.0f, 0.0f },
        0.0f,
        WHITE
    );
}

void Home::draw(){
    ClearBackground(RAYWHITE);

    Vector2 coords = playButton.getCoords();
    Rectangle source = {
        0.0f,
        0.0f,
        128.0f,
        64.0f
    };

    drawBackground();

    DrawTexturePro(
        *playButton.getSprite(),
        source,
        { coords.x, coords.y, BUTTON_WIDTH, BUTTON_HEIGHT },
        { 0.0f, 0.0f },
        0.0f,
        RAYWHITE
    );

    DrawText("PLAY", coords.x + 90, coords.y + 60, 130, RAYWHITE);
}

void Home::resetPage(){
    switchPage = PageType::COUNT;
}

void Home::handleInput(){
    Vector2 mousePosition = GetMousePosition();
        
    if(
        IsKeyReleased(KEY_P) ||
        (CheckCollisionPointRec(mousePosition, playButton.getRectangle()) && 
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    )
        switchPage = PageType::PLAY;
}

void Home::setAudioEngine(Audio *audioEngine){ 
    this->audioEngine = audioEngine; 
}

void Home::setVisualEngine(Visual *visualEngine){ 
    this->visualEngine = visualEngine; 

    playButton.setSprite(visualEngine->getUISprite(UI::BUTTON));
}