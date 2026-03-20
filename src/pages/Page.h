#pragma once
#include "raylib.h"
#include "../engine/Audio.h"
#include "../engine/Visual.h"

class Page{
protected:
    Audio *audioEngine;
    Visual *visualEngine;
    
    bool running;
    PageType switchPage = PageType::COUNT;

    virtual void handleInput() = 0;
public:
    Page();
    Page(Audio *audioEnding, Visual *visualEngine);
    virtual ~Page();

    virtual void setAudioEngine(Audio *audioEngine) = 0;
    virtual void setVisualEngine(Visual *visualEngine) = 0;

    const PageType getSwitchPage();
    const bool hasEngines();

    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void resetPage() = 0;
    const bool isRunning();
};