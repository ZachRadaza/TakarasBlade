#pragma once
#include "Page.h"
#include "../entities/Entity.h"
#include "../GameEngine.h"
#include "raylib.h"

class Home : public Page{
private:
    static constexpr float BUTTON_WIDTH = 128.0f * 4.0f;
    static constexpr float BUTTON_HEIGHT = 128.0f * 2.0f;

    Entity playButton;
    Entity background;

    void handleInput() override;

    void drawBackground();
public:
    Home();
    Home(Audio *audioEngine, Visual *visualEngine);
    ~Home();

    void update() override;
    void draw() override;
    void resetPage() override;

    void setAudioEngine(Audio *audioEngine) override;
    void setVisualEngine(Visual *visualEngine) override;
};