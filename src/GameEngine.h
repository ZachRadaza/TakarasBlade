#pragma once
#include "raylib.h"
#include "./pages/Page.h"
#include "./pages/HomePage.h"
#include "./pages/PlayPage.h"

class GameEngine{
private:
    static constexpr const float WINDOW_WIDTH  = 1280.0f;
    static constexpr const float WINDOW_HEIGHT = 720.0f;
    static constexpr const char *WINDOW_NAME = "Takara's Blade";

    Page *pages[2];
    Page *currentPage;

    Audio audioEngine;
    Visual visualEngine;

public:
    GameEngine();

    ~GameEngine();

    void gameLoop();

};