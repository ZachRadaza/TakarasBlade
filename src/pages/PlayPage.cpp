#include "PlayPage.h"
#include "raylib.h"

Play::Play()
    : Page(), 
    scaleSprites(0.0f),
    player(
        { (float) GetRenderWidth() / 2, (float) GetRenderHeight() / 2 },
        ENTITY_WIDTH, 
        ENTITY_HEIGHT, 
        nullptr, 
        TAKARA_SPEED, 
        TAKARA_RADIUS, 
        TAKARA_HEALTH, 
        TAKARA_ACCELARATION, 
        { 0.0f, 0.0f }
    ),
    enemies(),
    objects()
{}

Play::Play(Audio *audioEngine, Visual *visualEngine)
    : Page(audioEngine, visualEngine), 
    scaleSprites(0.0f),
    player(
        { (float) GetRenderWidth() / 2, (float) GetRenderHeight() / 2 },
        ENTITY_WIDTH, 
        ENTITY_HEIGHT, 
        visualEngine->getTakaraSprite(static_cast<int>(Action::STANCE)), 
        TAKARA_SPEED,
        TAKARA_RADIUS,
        TAKARA_HEALTH, 
        TAKARA_ACCELARATION,
        { 0.0f, 0.0f }
    ),
    enemies(),
    objects()
{}

Play::~Play(){

}

// Private
void Play::handleInput(){
    float x, y;
    x = y = 0;

    if(IsKeyDown(KEY_W))
        y -= 1;

    if(IsKeyDown(KEY_A))
        x -= 1;

    if(IsKeyDown(KEY_S))
        y += 1;

    if(IsKeyDown(KEY_D))
        x += 1;

    if(IsKeyPressed(KEY_SPACE))
        this->player.dash({x, y});
    
    if(IsKeyPressed(KEY_LEFT_SHIFT))
        this->player.parry();

    this->player.adjustCoords({ x, y }, TAKARA_ACCELARATION);
}

void Play::updatePlayer(){
    Vector2 orignalPlayerPosition { player.getCoords().x, player.getCoords().y };

    handleInput();

    if(checkCollisionObjects()){
        player.setCoords(orignalPlayerPosition);
    }
}

bool Play::dashInteraction(Character *charac1, Character *charac2){
    return             
        !charac2->isDead() &&
        collisionDetection(charac1, charac2) &&
        charac1->isDashing();
}

bool Play::collisionDetection(Entity *object1, Entity *object2){
    Vector2 object1Coords = object1->getCoords();
    Vector2 object2Coords = object2->getCoords();

    return (
        object2Coords.x < object1Coords.x + object1->getWidth() &&
        object2Coords.x + object2->getWidth() > object1Coords.x &&
        object2Coords.y < object1Coords.y + object1->getHeight() &&
        object2Coords.y + object2->getHeight() > object1Coords.y
    );
}

bool Play::checkCollisionObjects(){
    if(objects.size() == 0)
        return false;

    for(Entity &object : objects){
        if(collisionDetection(&player, &object))
            return true;
    }

    return false;
}

bool Play::circleDetection(Character *charac1, Character *charac2){
    Vector2 charac1Coords = charac1->getCoords();
    Vector2 charac2Coords = charac2->getCoords();

    float distanceX = charac1Coords.x - charac2Coords.x;
    float distanceY = charac1Coords.y - charac2Coords.y;

    float distanceSq = distanceX * distanceX + distanceY * distanceY;
    float radius = charac1->getRadius() + charac2->getRadius();

    return distanceSq <= radius * radius;
}

void Play::drawEntity(Entity *entity){
    Vector2 coords = entity->getCoords();
    Rectangle source;

    if(Character* charac = dynamic_cast<Character*>(entity)){
       Action lastAction = charac->getCurrentAction();

        source = entity->getSpriteSource();

        Action currentAction = charac->getCurrentAction();

        if(lastAction != currentAction){
            int currentActionIndex = static_cast<int>(currentAction);
            Texture2D* newSprite = visualEngine->getTakaraSprite(currentActionIndex);

            charac->setSprite(newSprite);
        }
    } else
        source = entity->getSpriteSource();

    DrawTexturePro(
        *entity->getSprite(), 
        source, 
        { coords.x, coords.y, ENTITY_HEIGHT, ENTITY_WIDTH }, 
        { 0.0f, 0.0f},
        0.0f,
        WHITE
    );
}

void Play::drawObjects(){
    for(int i = 0; i < objects.size(); i++){
        Entity object = objects.at(i);
        DrawRectangle(
            object.getCoords().x, 
            object.getCoords().y,
            object.getWidth(),
            object.getHeight(),
            BLACK
        );
    }
}

void Play::drawEnemies(){
    for(Character &enemy : enemies){
        drawEntity(&enemy);
    }
}

void Play::drawUI(){
    DrawText(TextFormat("Height: %d", GetScreenHeight()), 20, 20, 20, BLACK);
    DrawText(TextFormat("player height: %d", player.getSprite()->height), 20, 40, 20, BLACK);
    DrawText(TextFormat("player health: %d", player.getHealth()), 20, 60, 20, BLACK);
}


void Play::spawnEnemyWave(){
    for(int i = 0; i < ENEMIES_PER_SPAWN; i++){
        Vector2 spawnPoint{
            (float) GetRandomValue(0, GetRenderWidth() - ENTITY_HEIGHT),
            (float) GetRandomValue(0, GetRenderHeight() - ENTITY_WIDTH)
        };

        Character enemy(
            spawnPoint,
            ENTITY_WIDTH,
            ENTITY_HEIGHT,
            visualEngine->getTakaraSprite(static_cast<int>(Action::STANCE)), 
            CHARAC_SPEED,
            CHARAC_RADIUS,
            CHARAC_HEALTH,
            CHARAC_ACCELARATION,
            { 0.0f, 0.0f }
        );

        enemies.push_back(enemy);
    }

    enemiesToSpawn -= ENEMIES_PER_SPAWN;
    enemySpawnTimer = ENEMIES_SPAWN_RATE;
}

bool Play::areEnemiesDead(){
    if(enemies.size() == 0)
        return true;

    for(Character &enemy : enemies){
        if(!enemy.isDead())
            return false;
    }

    return true;
}

void Play::manageWave(){
    float downTime = GetFrameTime();

    if(enemiesToSpawn > 0 && enemySpawnTimer <= 0.0f)
        spawnEnemyWave();

    if(!areEnemiesDead() || enemiesToSpawn != 0){
        enemySpawnTimer -= downTime;
        return;
    }

    if(waveBreakTimer > 0.0f){
        waveBreakTimer -= downTime;
        return;
    }

    waveBreakTimer = WAVE_BREAK;
    enemies.clear();
    enemiesToSpawn = wave * BASE_NUM_ENEMIES;

    ++wave;
}

void Play::updateEnemyInteraction(Character &enemy){
    // player dashing to enemy
    if(dashInteraction(&player, &enemy))
        enemy.adjustHealth(-1);

    // enemy dashing to player
    if(dashInteraction(&enemy, &player) && !enemy.getHitsDash()){
        if(player.isParrying()){
            enemy.stun();
        } else if(!player.isDashing()){
            player.adjustHealth(-1);
            enemy.setHitsDash(true);
        }
    }
}

void Play::updateEnemyMovement(Character &enemy){
    Vector2 original = enemy.getCoords();
    float enemyAdjustX, enemyAdjustY;
    enemyAdjustX = enemyAdjustY = 0.0f;

    if(enemy.getCoords().x > player.getCoords().x + player.getWidth())
        enemyAdjustX = -1.0f;
    else if(enemy.getCoords().x < player.getCoords().x)
        enemyAdjustX = 1.0f;

    if(enemy.getCoords().y > player.getCoords().y + player.getWidth())
        enemyAdjustY = -1.0f;
    else if(enemy.getCoords().y < player.getCoords().y)
        enemyAdjustY = 1.0f;

    if(circleDetection(&player, &enemy) && !enemy.isDashing()){
        enemy.setHitsDash(false);
        enemy.dash({ enemyAdjustX, enemyAdjustY });
    }

    enemy.adjustCoords({ enemyAdjustX, enemyAdjustY }, FRICTION);
}

void Play::updateEnemies(){
    for(Character &enemy: enemies){
        if(enemy.isDead()){
            if(enemy.isDashing()) 
                enemy.adjustCoords({ 0.0f, 0.0f }, FRICTION);
            continue;
        }

        updateEnemyInteraction(enemy);
        updateEnemyMovement(enemy);
    }
}

// Public

void Play::update(){
    updatePlayer();

    manageWave();
    updateEnemies();
}

void Play::draw(){
    ClearBackground(RAYWHITE);

    drawObjects();

    drawEnemies();

    drawEntity(&player);

    drawUI();
}

void Play::setAudioEngine(Audio *audioEngine){ 
    this->audioEngine = audioEngine; 
}

void Play::setVisualEngine(Visual *visualEngine){ 
    this->visualEngine = visualEngine; 
    player.setSprite(
        visualEngine->getTakaraSprite(static_cast<int>(Action::STANCE))
    );
}