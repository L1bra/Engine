#pragma once

#include "window.h"
#include "input_handler.h"
#include "events/event_manager.h"


class Game
{
private:
    std::shared_ptr<IEventManager> em;

    Window* window;

    Shader* shader;
    Renderer* renderer;
    InputHandler* input_handler;
public:
    Game();
    ~Game();
    
    // load game stuff and init systems
    void init();

    // main loop
    void main_loop();

    // input -> update -> render
    void input();
    void update(float dt);
    void render();
};