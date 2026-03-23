#pragma once

enum class Action{
    STANCE,
    RUN,
    DASH,
    PARRY,
    STUN,
    DEAD,
    COUNT
};

enum class Direction{
    DOWN,
    TOP,
    LEFT,
    RIGHT
};

enum class Elements{
    SMOKE,
    SPARK,
    BLOOD,
    COUNT
};

enum class UI{
    PAUSE,
    WAVE,
    KILLS,
    HEALTH,
    DASH,
    PARRY,
    BUTTON,
    COUNT
};

enum class PageType{
    HOME,
    PLAY,
    COUNT
};

enum class ActionSounds{
    RUN,
    DASH,
    PARRY,
    DEAD,
    COUNT
};