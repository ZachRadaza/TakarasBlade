#pragma once
#include "raylib.h"

class Visual{
private:
    struct VisualFiles{
        static constexpr const char *TAKARA_FILE = "assets/images/big_guy.png";
    };

    Texture2D sprites[1];
public:
    enum class TexSprite{
        TAKARA,
        COUNT
    };

    Visual();
    ~Visual();

    void initTextures();

    Texture2D *getSprite(int index);
};