#pragma once
#include "Page.h"
#include "../entities/Character.h"

class Play : public Page{
private:
    static constexpr const float TAKARA_SPEED = 600.0f;
    static constexpr const float TAKARA_ACCELARATION = 1500.0f;
    static constexpr const float FRICTION = 800.0f;

    Character player;

    void handleInput() override;
public:
    Play();
    Play(Audio *audioEngine, Visual *visualEngine);
    ~Play();

    void update() override;
    void draw() override;

    void setAudioEngine(Audio *audioEngine) override;
    void setVisualEngine(Visual *visualEngine) override;

};