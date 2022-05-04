#include "game.h"


Game::Game()
    :
    em(new EventManager()),
    window(new Window("JRPG", 640, 480, em))
{
    shader = ResourceManager::load_shader("../../src/vertex.vs", "../../src/fragment.fs", nullptr, "sprite");
    renderer = new Renderer(shader);
}

Game::~Game()
{

}

void Game::init()
{
    main_loop();
}

void Game::main_loop()
{
    // TODO: dt

    while(window->is_open())
    {
        input();
        update();
        render();
    }
}

void Game::input()
{

}

void Game::update()
{
    window->update();
}

void Game::render()
{
    window->render(*renderer);
}