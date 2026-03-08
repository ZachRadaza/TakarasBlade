#include "GameEngine.h"
#include <iostream>

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

    pages[0] = new Home();

    pages[1] = new Play();

    for(int i = 0; i < 2; i++){
        pages[i]->setAudioEngine(&audioEngine);
        pages[i]->setVisualEngine(&visualEngine);
    }

    currentPage = pages[1];
}

GameEngine::~GameEngine(){
    std::cout << "crash";

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
    }
}