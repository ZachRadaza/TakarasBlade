#pragma once
#include "Page.h"
#include "../entities/Character.h"
#include "../engine/Action.h"
#include <vector>

class Play : public Page{
private:
    static constexpr float WALL_THICKNESS = 20.0f;
    
    static constexpr float TAKARA_SPEED = 600.0f;
    static constexpr float TAKARA_ACCELARATION = 1500.0f;
    static constexpr int TAKARA_HEALTH = 300;
    static constexpr float TAKARA_RADIUS = 250.0f;

    static constexpr float ENTITY_WIDTH = 128.0f;
    static constexpr float ENTITY_HEIGHT = 128.0f;

    static constexpr float CHARAC_SPEED = 450.0f;
    static constexpr float CHARAC_RADIUS = 100.0f;
    static constexpr float CHARAC_ACCELARATION = 1500.0f;
    static constexpr int CHARAC_HEALTH = 1;

    static constexpr float FRICTION = 800.0f;
    static constexpr int BASE_NUM_ENEMIES = 2;
    static constexpr int ENEMIES_PER_SPAWN = 1;
    static constexpr float ENEMIES_SPAWN_RATE = 1.0f;
    static constexpr float WAVE_BREAK = 4.0f;

    float scaleSprites;
    Character player;
    std::vector<Character> enemies;
    std::vector<Entity> objects;    

    int wave = 1;
    int enemiesToSpawn = 0;
    float waveBreakTimer = 0.0f;
    float enemySpawnTimer = 0.0f;

    void handleInput() override;
    void updatePlayer();
    bool dashInteraction(Character *charac1, Character *charac2);

    void drawEntity(Entity *entity);
    void drawObjects();
    void drawEnemies();

    void drawUI();

    bool collisionDetection(Entity *object1, Entity *object2);
    bool checkCollisionObjects();
    bool circleDetection(Character *charac1, Character *charac2);
    
    bool areEnemiesDead();
    void spawnEnemyWave();
    void updateEnemyInteraction(Character &enemy);
    void updateEnemyMovement(Character &enemy);
    void updateEnemies();

    void manageWave();
    
public:
    Play();
    Play(Audio *audioEngine, Visual *visualEngine);
    ~Play();

    void update() override;
    void draw() override;

    void setAudioEngine(Audio *audioEngine) override;
    void setVisualEngine(Visual *visualEngine) override;

};