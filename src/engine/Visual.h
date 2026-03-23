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

    static constexpr const char *ENEMY_STANCE = "assets/sprites/enemy/EnemyStance.png";
    static constexpr const char *ENEMY_RUN = "assets/sprites/enemy/EnemyRun.png";
    static constexpr const char *ENEMY_DASH = "assets/sprites/enemy/EnemyDash.png";
    static constexpr const char *ENEMY_PARRY = "assets/sprites/enemyEnemyParry.png";
    static constexpr const char *ENEMY_STUN = "assets/sprites/enemy/EnemyStun.png";
    static constexpr const char *ENEMY_DEAD = "assets/sprites/enemy/EnemyDead.png";

    static constexpr const char *GRASS = "assets/sprites/backgrounds/Grass3.png";
    static constexpr const char *GRASS_DETAILED = "assets/sprites/backgrounds/Grass.png";
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
    static constexpr const char *UI_BUTTON = "assets/sprites/ui/BigButton.png";

    Texture2D takaraSprites[static_cast<int>(Action::COUNT)];
    Texture2D enemySprites[static_cast<int>(Action::COUNT)];
    Texture2D background[static_cast<int>(PageType::COUNT)];
    Texture2D elementSprites[static_cast<int>(Elements::COUNT)];
    Texture2D uiSprites[static_cast<int>(UI::COUNT)];

    void initTakaraTextures();
    void initEnemyTextures();
    void initBackground();
    void initElementTextures();
    void initUiTextures();

public:
    Visual();
    ~Visual();

    void initTextures();

    Texture2D *getTakaraSprite(Action index);
    Texture2D *getEnemySprite(Action index);
    Texture2D *getBackground(PageType index);
    Texture2D *getElementSprite(Elements index);
    Texture2D *getUISprite(UI index);
};