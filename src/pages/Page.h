#pragma once
#include "raylib.h"
#include "../engine/Audio.h"
#include "../engine/Visual.h"

class Page{
protected:
    bool running;
    Audio *audioEngine;
    Visual *visualEngine;

    virtual void handleInput() = 0;
public:
    Page();
    Page(Audio *audioEnding, Visual *visualEngine);
    virtual ~Page();

    virtual void setAudioEngine(Audio *audioEngine) = 0;
    virtual void setVisualEngine(Visual *visualEngine) = 0;
    const bool hasEngines();

    virtual void update() = 0;
    virtual void draw() = 0;
    const bool isRunning();
};