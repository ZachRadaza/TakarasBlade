#include "Audio.h"

Audio::Audio()
    : takaraSounds(), enemySounds(), elementSounds() {}

Audio::~Audio(){
    for(Sound &sound : takaraSounds)
        UnloadSound(sound);

    for(Sound &sound : enemySounds)
        UnloadSound(sound);

    for(Sound &sound : elementSounds)
        UnloadSound(sound);

    UnloadMusicStream(homeMusic);
    UnloadMusicStream(playMusic);
}

void Audio::initAudios(){
    initTakaraSounds();
    initEnemySounds();
    initElementSounds();

    homeMusic = LoadMusicStream(MUSIC_HOME);
    playMusic = LoadMusicStream(MUSIC_PLAY);

    SetMusicVolume(playMusic, 0.7f);

    SetMasterVolume(0.5f);
}

void Audio::initTakaraSounds(){
    takaraSounds[static_cast<int>(ActionSounds::RUN)] = LoadSound(TAKARA_RUN);
    takaraSounds[static_cast<int>(ActionSounds::DASH)] = LoadSound(TAKARA_DASH);
    takaraSounds[static_cast<int>(ActionSounds::PARRY)] = LoadSound(TAKARA_PARRY);
    takaraSounds[static_cast<int>(ActionSounds::DEAD)] = LoadSound(TAKARA_DEAD);

    SetSoundVolume(takaraSounds[static_cast<int>(ActionSounds::DASH)], 0.3f);
    SetSoundVolume(takaraSounds[static_cast<int>(ActionSounds::PARRY)], 0.5f);
    SetSoundVolume(takaraSounds[static_cast<int>(ActionSounds::RUN)], 0.7f);

}

void Audio::initEnemySounds(){
    enemySounds[static_cast<int>(ActionSounds::RUN)] = LoadSound(ENEMY_RUN);
    enemySounds[static_cast<int>(ActionSounds::DASH)] = LoadSound(ENEMY_DASH);
    enemySounds[static_cast<int>(ActionSounds::PARRY)] = LoadSound(ENEMY_PARRY);
    enemySounds[static_cast<int>(ActionSounds::DEAD)] = LoadSound(ENEMY_DEAD);

    SetSoundVolume(enemySounds[static_cast<int>(ActionSounds::DEAD)], 0.2f);
}

void Audio::initElementSounds(){
    elementSounds[static_cast<int>(Elements::BLOOD)] = LoadSound(KILL);
    elementSounds[static_cast<int>(Elements::SPARK)] = LoadSound(PARRY);
    elementSounds[static_cast<int>(Elements::SMOKE)] = LoadSound(SMOKE);

    SetSoundVolume(elementSounds[static_cast<int>(Elements::SMOKE)], 1.2f);
    SetSoundVolume(elementSounds[static_cast<int>(Elements::BLOOD)], 1.0f);
}

void Audio::playTakaraSounds(ActionSounds sound){
    PlaySound(takaraSounds[static_cast<int>(sound)]);
}

void Audio::playEnemySounds(ActionSounds sound){
    PlaySound(enemySounds[static_cast<int>(sound)]);
}

void Audio::playElementSounds(Elements sound){
    PlaySound(elementSounds[static_cast<int>(sound)]);
}

void Audio::playHomeMusic(){
    PlayMusicStream(homeMusic);
}

void Audio::playPlayMusic(){
    PlayMusicStream(playMusic);
}

void Audio::updateHomeMusic(){
    UpdateMusicStream(homeMusic);
}

void Audio::updatePlayMusic(){
    UpdateMusicStream(playMusic);
}

void Audio::stopTakaraSound(ActionSounds sound){
    StopSound(takaraSounds[static_cast<int>(sound)]);
}

void Audio::stopAllTakaraSounds(){
    for(Sound &sound : takaraSounds)
        StopSound(sound);
}

void Audio::stopAllEnemySounds(){
    for(Sound &sound : takaraSounds)
        StopSound(sound);
}

bool Audio::isTakaraRunning(){
    return IsSoundPlaying(takaraSounds[static_cast<int>(ActionSounds::RUN)]);
}

bool Audio::isHomeMusicPlaying(){
    return IsMusicStreamPlaying(homeMusic);
}

bool Audio::isPlayMusicPlaying(){
    return IsMusicStreamPlaying(playMusic);
}