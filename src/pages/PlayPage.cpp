#include "PlayPage.h"
#include "raylib.h"

Play::Play()
    : Page(), 
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
    uiElements()
{}

Play::Play(Audio *audioEngine, Visual *visualEngine)
    : Page(audioEngine, visualEngine), 
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
    uiElements()
{
    initUI();
}

Play::~Play(){

}

// Private

void Play::initUI(){
    std::unordered_map<int, Vector2> coords;
    float yBottom = GetRenderHeight() - ENTITY_HEIGHT;

    coords[static_cast<int>(UI::HEALTH)] = { 0.0f, yBottom };
    coords[static_cast<int>(UI::DASH)] = { ENTITY_WIDTH, yBottom };
    coords[static_cast<int>(UI::PARRY)] = { ENTITY_WIDTH * 2, yBottom };
    coords[static_cast<int>(UI::PAUSE)] = { 0.0f, 0.0f };
    coords[static_cast<int>(UI::WAVE)] = { 0.0f, ENTITY_HEIGHT };
    coords[static_cast<int>(UI::KILLS)] = { 0.0f, ENTITY_HEIGHT * 2 };

    for(int i = 0; i < sizeof(uiElements) / sizeof(uiElements[0]); i++){
        uiElements[i] = {
            coords[i],
            ENTITY_WIDTH,
            ENTITY_HEIGHT,
            visualEngine->getUISprite(i),
            0.0f
        };
    }
}

void Play::handleInput(){
    float x, y;
    x = y = 0;

    if(IsKeyPressed(KEY_R))
        restartGame();

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

bool Play::dashInteraction(Character *charac1, Character *charac2){
    return             
        !charac2->isDead() &&
        collisionDetection(charac1, charac2) &&
        charac1->isDashing();
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

bool Play::circleDetection(Character *charac1, Character *charac2){
    Vector2 charac1Coords = charac1->getCoords();
    Vector2 charac2Coords = charac2->getCoords();

    float distanceX = charac1Coords.x - charac2Coords.x;
    float distanceY = charac1Coords.y - charac2Coords.y;

    float distanceSq = distanceX * distanceX + distanceY * distanceY;
    float radius = charac1->getRadius() + charac2->getRadius();

    return distanceSq <= radius * radius;
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

    wave++;

    waveBreakTimer = WAVE_BREAK;
    enemies.clear();
    enemiesToSpawn = wave * BASE_NUM_ENEMIES;
}

void Play::updateEnemyInteraction(Character &enemy){
    if(enemy.isDead())
        return;

    // player dashing to enemy
    if(dashInteraction(&player, &enemy)){
        enemy.adjustHealth(-1);
        
        if(enemy.isDead())
            kills++;
    } else if(dashInteraction(&enemy, &player) && !enemy.getHitsDash()){ // enemy dashing to player
        if(player.isParrying()){
            enemy.stun();
        } else {
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
        updateEnemyInteraction(enemy);
        updateEnemyMovement(enemy);
    }
}

void Play::updateUI(){
    if(player.isDashing())
        uiElements[static_cast<int>(UI::DASH)].setCurrentDirection(Direction::TOP);
    else if(player.getDashCooldown() > 0.0f)
        uiElements[static_cast<int>(UI::DASH)].setCurrentDirection(Direction::LEFT);
    else
        uiElements[static_cast<int>(UI::DASH)].setCurrentDirection(Direction::DOWN);
    
    if(player.isParrying())
        uiElements[static_cast<int>(UI::PARRY)].setCurrentDirection(Direction::TOP);
    else if(player.getParryCooldown() > 0.0f)
        uiElements[static_cast<int>(UI::PARRY)].setCurrentDirection(Direction::LEFT);
    else
        uiElements[static_cast<int>(UI::PARRY)].setCurrentDirection(Direction::DOWN);

    int healthIndex = std::abs(3 - player.getHealth());
    uiElements[static_cast<int>(UI::HEALTH)].setCurrentDirection((Direction) healthIndex);
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
        { coords.x, coords.y, ENTITY_WIDTH, ENTITY_HEIGHT }, 
        { 0.0f, 0.0f},
        0.0f,
        WHITE
    );
}

void Play::drawEnemies(){
    std::vector<Character*> entities;
    entities.clear();

    for(Character &enemy : enemies)
        entities.push_back(&enemy);

    std::sort(entities.begin(), entities.end(),
        [](const Character* a, const Character* b) {
            return a->getCoords().y < b->getCoords().y;
        }
    );

    for(Character *&charac : entities){
        drawEntity(charac);
    }
}

void Play::drawBackground(){
    float screenWidth = static_cast<float>(GetRenderWidth());
    float screenHeight = static_cast<float>(GetRenderHeight());
    float scale = 4.0f;

    Rectangle source = { 0, 0, screenWidth / scale, screenHeight / scale };
    Rectangle dest = { 0, 0, screenWidth, screenHeight };
    
    DrawTexturePro(
        *visualEngine->getBackground(),
        source,
        dest,
        { 0.0f, 0.0f },
        0.0f,
        WHITE
    );
}

void Play::drawUI(){
    for(int i = 0; i < sizeof(uiElements) / sizeof(uiElements[0]); i++){
        Vector2 coords = uiElements[i].getCoords();
        DrawTexturePro(
            *uiElements[i].getSprite(),
            uiElements[i].getSpriteSource(),
            { coords.x, coords.y, uiElements[i].getWidth(), uiElements[i].getHeight() },
            { 0.0f, 0.0f },
            0.0f,
            WHITE
        );
    }

    DrawText("WAVE", 20.0f, ENTITY_HEIGHT + 20.0f, 30, WHITE);
    DrawText(TextFormat("%d", wave), 50.0f, ENTITY_HEIGHT + 55.0f, 50, WHITE);

    DrawText("KILLS", 20.0f, (ENTITY_HEIGHT * 2) + 20.0f, 30, WHITE);
    DrawText(TextFormat("%d", kills), 45.0f, (ENTITY_HEIGHT * 2) + 55.0f, 50, WHITE);
}

void Play::restartGame(){
    wave = 0;
    kills = 0;
    enemiesToSpawn = 0;
    waveBreakTimer = 0.0f;
    enemySpawnTimer = 0.0f;
    enemies.clear();

    player.setHealth(TAKARA_HEALTH);
    player.setCoords({ (float) GetRenderWidth() / 2, (float) GetRenderHeight() / 2 });
}

// Public

void Play::update(){
    handleInput();

    manageWave();
    updateEnemies();

    updateUI();
}

void Play::draw(){
    ClearBackground(RAYWHITE);

    drawBackground();

    if(player.isDead())
        drawEntity(&player);

    drawEnemies();

    if(!player.isDead())
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

    initUI();
}