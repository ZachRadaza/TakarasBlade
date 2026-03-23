#pragma once
#include "Enums.h"
#include "raylib.h"

class Audio{
private:
    static constexpr const char *TAKARA_DASH = "assets/audios/takara/TakaraDash.wav";
    static constexpr const char *TAKARA_RUN = "assets/audios/takara/TakaraRun.wav";
    static constexpr const char *TAKARA_PARRY = "assets/audios/takara/TakaraParry.wav";
    static constexpr const char *TAKARA_DEAD = "assets/audios/takara/TakaraDead.wav";

    static constexpr const char *ENEMY_DASH = "assets/audios/enemy/EnemyDash.wav";
    static constexpr const char *ENEMY_RUN = "assets/audios/enemy/TakaraRun.wav";
    static constexpr const char *ENEMY_PARRY = "assets/audios/enemy/TakaraParry.wav";
    static constexpr const char *ENEMY_DEAD = "assets/audios/enemy/EnemyDead.wav";

    static constexpr const char *KILL = "assets/audios/elements/Kill.wav";
    static constexpr const char *PARRY = "assets/audios/elements/Parry.wav";
    static constexpr const char *SMOKE = "assets/audios/elements/Smoke.wav";

    static constexpr const char *MUSIC_HOME = "assets/audios/music/HomeMusic.wav";
    static constexpr const char *MUSIC_PLAY = "assets/audios/music/PlayMusic.wav";

    Sound takaraSounds[static_cast<int>(ActionSounds::COUNT)];
    Sound enemySounds[static_cast<int>(ActionSounds::COUNT)];
    Sound elementSounds[static_cast<int>(Elements::COUNT)];

    Music homeMusic;
    Music playMusic;

    void initTakaraSounds();
    void initEnemySounds();
    void initElementSounds();

public:
    Audio();
    ~Audio();

    void initAudios();

    void playTakaraSounds(ActionSounds sound);
    void playEnemySounds(ActionSounds sound);
    void playElementSounds(Elements sound);
    void playHomeMusic();
    void playPlayMusic();

    void updateHomeMusic();
    void updatePlayMusic();

    void stopTakaraSound(ActionSounds sound);
    void stopAllTakaraSounds();
    void stopAllEnemySounds();

    bool isTakaraRunning();
    bool isHomeMusicPlaying();
    bool isPlayMusicPlaying();
};
