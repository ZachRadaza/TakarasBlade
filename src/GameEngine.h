#pragma once
#include "raylib.h"
#include "./engine/Enums.h"
#include "./engine/Audio.h"
#include "./engine/Visual.h"
#include "./pages/Page.h"
#include "./pages/HomePage.h"
#include "./pages/PlayPage.h"

class GameEngine{
private:
    static constexpr const float WINDOW_WIDTH  = 1280.0f;
    static constexpr const float WINDOW_HEIGHT = 720.0f;
    static constexpr const char *WINDOW_NAME = "Takara's Blade";

    Page *pages[static_cast<int>(PageType::COUNT)];
    Page *currentPage;

    Audio audioEngine;
    Visual visualEngine;

public:
    GameEngine();
    ~GameEngine();

    void gameLoop();

    void openPage(PageType page);
};