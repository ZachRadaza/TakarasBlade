#pragma once
#include "raylib.h"
#include "./Action.h"

class Visual{
private:
    static constexpr const char *TAKARA_STANCE = "assets/sprites/takara/TakaraStance.png";
    static constexpr const char *TAKARA_RUN = "assets/sprites/takara/TakaraRun.png";
    static constexpr const char *TAKARA_DASH = "assets/sprites/takara/TakaraDash.png";
    static constexpr const char *TAKARA_PARRY = "assets/sprites/takara/TakaraParry.png";
    static constexpr const char *TAKARA_STUN = "assets/sprites/takara/TakaraStance.png";
    static constexpr const char *TAKARA_DEAD = "assets/sprites/takara/TakaraDead.png";

    Texture2D takaraSprites[static_cast<int>(Action::COUNT)];

    void initTakaraTextures();

public:
    Visual();
    ~Visual();

    void initTextures();

    Texture2D *getTakaraSprite(int index);
};