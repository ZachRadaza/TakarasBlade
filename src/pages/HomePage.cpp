#include "HomePage.h"

Home::Home()
    : Page() {

}

Home::~Home(){

}

void Home::update(){
    handleInput();
}

void Home::draw(){
    ClearBackground(RAYWHITE);
}

void Home::resetPage(){
    switchPage = PageType::COUNT;
}

void Home::handleInput(){
    if(IsKeyReleased(KEY_P))
        switchPage = PageType::PLAY;
}

void Home::setAudioEngine(Audio *audioEngine){ 
    this->audioEngine = audioEngine; 
}

void Home::setVisualEngine(Visual *visualEngine){ 
    this->visualEngine = visualEngine; 
}