#include "PlayPage.h"

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
    bloodElements(),
    elements(),
    uiComponents()
{}

Play::Play(Audio *audioEngine, Visual *visualEngine)
    : Page(audioEngine, visualEngine), 
    player(
        { (float) GetRenderWidth() / 2, (float) GetRenderHeight() / 2 },
        ENTITY_WIDTH, 
        ENTITY_HEIGHT, 
        visualEngine->getTakaraSprite(Action::STANCE), 
        TAKARA_SPEED,
        TAKARA_RADIUS,
        TAKARA_HEALTH, 
        TAKARA_ACCELARATION,
        { 0.0f, 0.0f }
    ),
    enemies(),
    bloodElements(),
    elements(),
    uiComponents()
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
    coords[static_cast<int>(UI::BUTTON)] = { 0.0f, ENTITY_HEIGHT * 2 };

    for(int i = 0; i < sizeof(uiComponents) / sizeof(uiComponents[0]); i++){
        UI index = static_cast<UI>(i);

        uiComponents[i] = {
            coords[i],
            ENTITY_WIDTH,
            ENTITY_HEIGHT,
            visualEngine->getUISprite(index),
            0.0f
        };
    }
}

void Play::handleInput(){
    Vector2 mousePosition = GetMousePosition();

    if(IsKeyReleased(KEY_P))
        switchPage = PageType::HOME;

    if(IsKeyPressed(KEY_R))
        restartGame();

    if(
        IsKeyPressed(KEY_TAB) ||
        (CheckCollisionPointRec(mousePosition, uiComponents[static_cast<int>(UI::PAUSE)].getRectangle()) && 
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    )
        pauseGame();
}

void Play::handlePlayerInput(){
    float x, y;
    x = y = 0;
    Vector2 mousePosition = GetMousePosition();

    if(IsKeyDown(KEY_W))
        y -= 1;

    if(IsKeyDown(KEY_A))
        x -= 1;

    if(IsKeyDown(KEY_S))
        y += 1;

    if(IsKeyDown(KEY_D))
        x += 1;

    if(
        IsKeyPressed(KEY_SPACE) ||
        (CheckCollisionPointRec(mousePosition, uiComponents[static_cast<int>(UI::DASH)].getRectangle()) && 
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    ){
        this->player.dash({x, y});
        audioEngine->stopTakaraSound(ActionSounds::RUN);
        audioEngine->playTakaraSounds(ActionSounds::DASH);
    }

    if(
        IsKeyPressed(KEY_LEFT_SHIFT) ||
        (CheckCollisionPointRec(mousePosition, uiComponents[static_cast<int>(UI::PARRY)].getRectangle()) && 
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    ){
        this->player.parry();
        audioEngine->stopTakaraSound(ActionSounds::RUN);
        audioEngine->playTakaraSounds(ActionSounds::PARRY);
    }

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

void Play::addElement(Vector2 coords, Elements elementType){
    Entity element(
        coords,
        ENTITY_WIDTH,
        ENTITY_HEIGHT,
        visualEngine->getElementSprite(elementType),
        0.0f
    );

    if(elementType == Elements::BLOOD){
        element.setCurrentDirection(Direction::LEFT);

        bloodElements.push_back(element);
    } else
        elements.push_back(element);

    audioEngine->playElementSounds(elementType);
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
            visualEngine->getEnemySprite(Action::STANCE), 
            CHARAC_SPEED,
            CHARAC_RADIUS,
            CHARAC_HEALTH,
            CHARAC_ACCELARATION,
            { 0.0f, 0.0f }
        );

        enemies.push_back(enemy);
        addElement(enemy.getCoords(), Elements::SMOKE);
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
    elements.clear();
    enemiesToSpawn = wave * BASE_NUM_ENEMIES;
}

void Play::updateEnemyInteraction(Character &enemy){
    if(enemy.isDead())
        return;

    // player dashing to enemy
    if(dashInteraction(&player, &enemy)){
        enemy.adjustHealth(-1);
        
        if(enemy.isDead()){
            kills++;
            addElement(enemy.getCoords(), Elements::BLOOD);
            audioEngine->playEnemySounds(ActionSounds::DEAD);
        }
    } else if(dashInteraction(&enemy, &player) && !enemy.getHitsDash()){ // enemy dashing to player
        if(player.isParrying()){
            enemy.stun();

            addElement(player.getCoords(), Elements::SPARK);
        } else if(!enemy.isStunned()){
            player.adjustHealth(-1);
            enemy.setHitsDash(true);

            addElement(player.getCoords(), Elements::BLOOD);

            if(player.isDead()){
                audioEngine->stopAllEnemySounds();
                audioEngine->playTakaraSounds(ActionSounds::DEAD);
            }
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

    if(circleDetection(&player, &enemy) && !enemy.isDashing() && !enemy.isDead()){
        enemy.setHitsDash(false);
        enemy.dash({ enemyAdjustX, enemyAdjustY });
        audioEngine->playEnemySounds(ActionSounds::DASH);
    }

    enemy.adjustCoords({ enemyAdjustX, enemyAdjustY }, FRICTION);
}

void Play::updateEnemies(){
    for(Character &enemy: enemies){
        if(!enemy.isDead())
            updateEnemyInteraction(enemy);
            
        updateEnemyMovement(enemy);
    }
}

void Play::updateElements(){
    for(int i = 0; i < elements.size(); i++){
        Entity *currentEl = &elements.at(i);

        if(currentEl->getAnimatedOnce()){
            Texture2D *texture = currentEl->getSprite();

            elements.erase(elements.begin() + i);
            i--;
        }
    }

    for(int i = 0; i < bloodElements.size(); i++){
        if(bloodElements.at(i).getAnimatedOnce())
            bloodElements.at(i).setCurrentDirection(Direction::RIGHT);
    }
}

void Play::updateUI(){
    if(player.isDashing())
        uiComponents[static_cast<int>(UI::DASH)].setCurrentDirection(Direction::TOP);
    else if(player.getDashCooldown() > 0.0f)
        uiComponents[static_cast<int>(UI::DASH)].setCurrentDirection(Direction::LEFT);
    else
        uiComponents[static_cast<int>(UI::DASH)].setCurrentDirection(Direction::DOWN);
    
    if(player.isParrying())
        uiComponents[static_cast<int>(UI::PARRY)].setCurrentDirection(Direction::TOP);
    else if(player.getParryCooldown() > 0.0f)
        uiComponents[static_cast<int>(UI::PARRY)].setCurrentDirection(Direction::LEFT);
    else
        uiComponents[static_cast<int>(UI::PARRY)].setCurrentDirection(Direction::DOWN);

    int healthIndex = std::abs(3 - player.getHealth());
    uiComponents[static_cast<int>(UI::HEALTH)].setCurrentDirection((Direction) healthIndex);
}

void Play::updateSounds(){
    Vector2 velocity = player.getVelocoty();

    if((velocity.x != 0 || velocity.y != 0) && !player.isDashing()){
        if(!audioEngine->isTakaraRunning())
            audioEngine->playTakaraSounds(ActionSounds::RUN);
    } else if(velocity.x == 0 && velocity.y == 0 && !player.isDashing()){
        if(audioEngine->isTakaraRunning())
            audioEngine->stopTakaraSound(ActionSounds::RUN);
    }

    if(!audioEngine->isPlayMusicPlaying())
        audioEngine->playPlayMusic();

    audioEngine->updatePlayMusic();
}

void Play::drawEntity(Entity *entity){
    Vector2 coords = entity->getCoords();
    Rectangle source;

    if(Character* charac = dynamic_cast<Character*>(entity)){
       Action lastAction = charac->getCurrentAction();

        source = entity->getSpriteSource();

        Action currentAction = charac->getCurrentAction();

        if(lastAction != currentAction){
            Texture2D* newSprite;
            if(entity == &player)
                newSprite = visualEngine->getTakaraSprite(currentAction);
            else
                newSprite = visualEngine->getEnemySprite(currentAction);

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
    std::vector<Entity*> entities;
    entities.clear();

    for(Entity &enemy : enemies)
        entities.push_back(&enemy);

    for(Entity &element : elements)
        entities.push_back(&element);

    std::sort(entities.begin(), entities.end(),
        [](const Entity* a, const Entity* b) {
            return a->getCoords().y < b->getCoords().y;
        }
    );

    for(Entity *&charac : entities){
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
        *visualEngine->getBackground(PageType::PLAY),
        source,
        dest,
        { 0.0f, 0.0f },
        0.0f,
        WHITE
    );
}

void Play::drawBlood(){
    for(Entity &blood : bloodElements)
        drawEntity(&blood);
}

void Play::drawUI(){
    for(int i = 0; i < sizeof(uiComponents) / sizeof(uiComponents[0]); i++){
        if(static_cast<UI>(i) == UI::BUTTON)
            continue;

        Vector2 coords = uiComponents[i].getCoords();
        DrawTexturePro(
            *uiComponents[i].getSprite(),
            uiComponents[i].getSpriteSource(),
            { coords.x, coords.y, uiComponents[i].getWidth(), uiComponents[i].getHeight() },
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

void Play::drawPaused(){
    DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(), Fade(BLACK, 0.5f));

    DrawText("PAUSED", GetRenderWidth() / 3, 200, 50, RAYWHITE);

    DrawText("CONTROLS", GetRenderWidth() / 3, 380, 50, RAYWHITE);
    DrawText("W, A, S, D -> Movement", GetRenderWidth() / 3, 450, 40, RAYWHITE);
    DrawText("SPACE -> Dash", GetRenderWidth() / 3, 500, 40, RAYWHITE);
    DrawText("SHIFT -> Parry", GetRenderWidth() / 3, 550, 40, RAYWHITE);
    DrawText("R -> Restart Game", GetRenderWidth() / 3, 600, 40, RAYWHITE);
    DrawText("Tab -> Pause Game", GetRenderWidth() / 3, 650, 40, RAYWHITE);
    DrawText("P -> Home Page", GetRenderWidth() / 3, 700, 40, RAYWHITE);
    DrawText("ESCAPE -> Close Game", GetRenderWidth() / 3, 750, 40, RAYWHITE);

}

void Play::restartGame(){
    wave = 0;
    kills = 0;
    enemiesToSpawn = 0;
    waveBreakTimer = 0.0f;
    enemySpawnTimer = 0.0f;
    enemies.clear();
    elements.clear();
    bloodElements.clear();

    player.setHealth(TAKARA_HEALTH);
    player.setCoords({ (float) GetRenderWidth() / 2, (float) GetRenderHeight() / 2 });

    switchPage = PageType::COUNT;
}

void Play::pauseGame(){
    Direction pauseState;
    if(!paused)
        pauseState = Direction::LEFT;
    else
        pauseState = Direction::DOWN;

    uiComponents[static_cast<int>(UI::PAUSE)].setCurrentDirection(pauseState);

    paused = !paused;
}

// Public

void Play::update(){
    handleInput();

    if(!paused){
        handlePlayerInput();

        manageWave();
        updateEnemies();

        updateElements();
        updateUI();
        updateSounds();
    }
}

void Play::draw(){
    ClearBackground(RAYWHITE);

    drawBackground();

    drawBlood();

    if(player.isDead())
        drawEntity(&player);

    drawEnemies();

    if(!player.isDead())
        drawEntity(&player);

    drawUI();

    if(paused)
        drawPaused();
}

void Play::resetPage(){
    restartGame();
}

void Play::setAudioEngine(Audio *audioEngine){ 
    this->audioEngine = audioEngine; 
}

void Play::setVisualEngine(Visual *visualEngine){ 
    this->visualEngine = visualEngine; 

    player.setSprite(
        visualEngine->getTakaraSprite(Action::STANCE)
    );

    initUI();
}
