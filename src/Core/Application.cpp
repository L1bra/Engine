#include "Application.h"


Application::Application(std::shared_ptr<IEventManager> EventManager)
    :
    EventListener(EventManager),
    m_EventManager(EventManager),
    m_Input_handler(std::make_unique<InputHandler>(this->m_EventManager)),
    m_Window(std::make_unique<Window>("JRPG", 640, 480, this->m_EventManager))
{
    on_event<WindowResizeEvent>([&](std::shared_ptr<WindowResizeEvent> data)
    {
        return OnWindowResize(data->GetWidth(), data->GetHeight());
    });

    on_event<WindowCloseEvent>([&](std::shared_ptr<WindowCloseEvent> data)
    {
        return OnWindowClose();
    });

    this->OnInit();
}

Application::~Application()
{
    this->OnShutdown();
}

void Application::OnInit()
{
    Global::ResourceManager::Init();
    MainLoop();
}

void Application::OnShutdown()
{
    Global::ResourceManager::Shutdown();
}

void Application::MainLoop()
{
    float delta_time = 0.0f;
    float last_frame = 0.0f;

    while(m_Window->IsOpen())
    {
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        this->Input();
        this->Update(delta_time);
        this->Render();
    }
}

void Application::Input()
{
    if(m_Input_handler->is_key_down(InputHandler::Key::ENTER)) printf("Enter is pressed!\n");
    if(m_Input_handler->is_key_down(InputHandler::Key::ESC)) printf("ESC is pressed!\n");
    if(m_Input_handler->is_key_pressed(InputHandler::Key::W)) printf("W is pressed!\n");
    if(m_Input_handler->is_key_pressed(InputHandler::Key::A)) printf("A is pressed!\n");
    if(m_Input_handler->is_key_pressed(InputHandler::Key::S)) printf("S is pressed!\n");
    if(m_Input_handler->is_key_pressed(InputHandler::Key::D)) printf("D is pressed!\n");
}

void Application::Update(float dt)
{
    m_Input_handler->update();
    m_Window->Update(dt);
}

void Application::Render()
{
    m_Window->Render();
}

void Application::Close()
{
    m_Running = false;
}

bool Application::OnWindowResize(int width, int height)
{
    if (width == 0 || height == 0)
    {
        m_Minimized = true;
        return false;
    }

    m_Minimized = false;
    return false;
}

bool Application::OnWindowClose()
{
    m_Running = false;
    return true;
}