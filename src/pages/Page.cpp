#include "Page.h"

Page::Page()
    : running(false), audioEngine(nullptr), visualEngine(nullptr){}

Page::Page(Audio *audioEngine, Visual *visualEngine)
    : running(false), audioEngine(audioEngine), visualEngine(visualEngine) {}

Page::~Page(){
}

const bool Page::hasEngines(){
    return 
        visualEngine != nullptr && 
        audioEngine != nullptr;
}

const PageType Page::getSwitchPage(){ return switchPage; }

const bool Page::isRunning(){
    return running;
}