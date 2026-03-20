#pragma once
#include "raylib.h"
#include "./Enums.h"

class Visual{
private:
    static constexpr const char *TAKARA_STANCE = "assets/sprites/takara/TakaraStance.png";
    static constexpr const char *TAKARA_RUN = "assets/sprites/takara/TakaraRun.png";
    static constexpr const char *TAKARA_DASH = "assets/sprites/takara/TakaraDash.png";
    static constexpr const char *TAKARA_PARRY = "assets/sprites/takara/TakaraParry.png";
    static constexpr const char *TAKARA_STUN = "assets/sprites/takara/TakaraStun.png";
    static constexpr const char *TAKARA_DEAD = "assets/sprites/takara/TakaraDead.png";

    static constexpr const char *GRASS = "assets/sprites/backgrounds/Grass3.png";
    static constexpr const char *WOOD = "assets/sprites/backgrounds/Wood.png";

    static constexpr const char *ELEMENT_BLOOD = "assets/sprites/elements/Blood.png";
    static constexpr const char *ELEMENT_SMOKE = "assets/sprites/elements/Smoke.png";
    static constexpr const char *ELEMENT_SPARK = "assets/sprites/elements/Spark.png";

    static constexpr const char *UI_PAUSE = "assets/sprites/ui/Pause.png";
    static constexpr const char *UI_WAVE = "assets/sprites/ui/Base.png";
    static constexpr const char *UI_KILLS = "assets/sprites/ui/Base.png";
    static constexpr const char *UI_HEALTH = "assets/sprites/ui/Health.png";
    static constexpr const char *UI_DASH = "assets/sprites/ui/Dash.png";
    static constexpr const char *UI_PARRY = "assets/sprites/ui/Parry.png";

    Texture2D takaraSprites[static_cast<int>(Action::COUNT)];
    Texture2D background;
    Texture2D elementSprites[static_cast<int>(Elements::COUNT)];
    Texture2D uiSprites[static_cast<int>(UI::COUNT)];

    void initTakaraTextures();
    void initBackground();
    void initElementTextures();
    void initUiTextures();

public:
    Visual();
    ~Visual();

    void initTextures();

    Texture2D *getTakaraSprite(int index);
    Texture2D *getBackground();
    Texture2D *getElementSprite(int index);
    Texture2D *getUISprite(int index);
};