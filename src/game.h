#pragma once

#include "window.h"
#include "events/event_manager.h"


class Game
{
private:
    std::shared_ptr<IEventManager> em;

    Window* window;

    Shader* shader;
    Renderer* renderer;
public:
    Game();
    ~Game();

    void init();
    void start();

    void main_loop();

    void input();
    void update();
    void render();
};