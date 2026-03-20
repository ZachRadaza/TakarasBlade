#pragma once
#include "Page.h"
#include "../GameEngine.h"
#include "raylib.h"

class Home : public Page{
private:

    void handleInput() override;
public:
    Home();
    ~Home();

    void update() override;
    void draw() override;
    void resetPage() override;

    void setAudioEngine(Audio *audioEngine) override;
    void setVisualEngine(Visual *visualEngine) override;
};