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
    COUNT
};

enum class PageType{
    HOME,
    PLAY,
    COUNT
};