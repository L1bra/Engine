#include "game.h"


Game::Game()
    :
    em(new EventManager()),
    window(new Window("JRPG", 640, 480, em)),
    shader(ResourceManager::load_shader("../../src/shaders/vertex.vs", "../../src/shaders/fragment.fs", nullptr, "sprite")),
    renderer(new Renderer(*shader)),
    input_handler(new InputHandler(em))
{
}

Game::~Game()
{
    // delete shaders
    ResourceManager::clear();

    delete input_handler;
    delete renderer;
    delete window;

}

void Game::init()
{
    main_loop();
}

void Game::main_loop()
{
    float delta_time = 0.0f;
    float last_frame = 0.0f;

    while(window->is_open())
    {
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        input();
        update(delta_time);
        render();
    }
}

void Game::input()
{
    if(input_handler->is_key_down(InputHandler::Key::ENTER)) printf("Enter is pressed!\n");
    if(input_handler->is_key_down(InputHandler::Key::ESC)) printf("ESC is pressed!\n");
    if(input_handler->is_key_pressed(InputHandler::Key::W)) printf("W is pressed!\n");
    if(input_handler->is_key_pressed(InputHandler::Key::A)) printf("A is pressed!\n");
    if(input_handler->is_key_pressed(InputHandler::Key::S)) printf("S is pressed!\n");
    if(input_handler->is_key_pressed(InputHandler::Key::D)) printf("D is pressed!\n");
}

void Game::update(float dt)
{
    input_handler->update();
    window->update(dt);
}

void Game::render()
{
    window->render(*renderer);
}