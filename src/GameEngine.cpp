#include "GameEngine.h"

void initializeWindow(float width, float height, const char *name){
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(width, height, name);

    ToggleFullscreen();

    SetTargetFPS(60);
}

GameEngine::GameEngine()
    : pages(), currentPage(nullptr), audioEngine(), visualEngine()
{
    initializeWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
    InitAudioDevice();

    visualEngine.initTextures();

    pages[static_cast<int>(PageType::HOME)] = new Home();

    pages[static_cast<int>(PageType::PLAY)] = new Play();

    for(int i = 0; i < 2; i++){
        pages[i]->setAudioEngine(&audioEngine);
        pages[i]->setVisualEngine(&visualEngine);
    }

    currentPage = pages[static_cast<int>(PageType::PLAY)];
}

GameEngine::~GameEngine(){
    for(Page *&page : pages){
        delete page;
    }

    CloseAudioDevice();
    CloseWindow();
}

void GameEngine::gameLoop(){
    while(!WindowShouldClose()){
        if(!currentPage->hasEngines())
            continue;

        currentPage->update();

        BeginDrawing();
        currentPage->draw();
        EndDrawing();

        PageType pageType = currentPage->getSwitchPage();
        if(pageType != PageType::COUNT)
            openPage(pageType);
    }
}

void GameEngine::openPage(PageType page){
    currentPage = pages[static_cast<int>(page)];

    currentPage->resetPage();
}