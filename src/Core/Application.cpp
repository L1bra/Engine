#include "Application.h"


Application::Application()
{
    this->OnInit();
}

Application::~Application()
{
    this->OnShutdown();
}

void Application::OnInit()
{
    Global::ResourceManager::Init();

    m_EventManager = std::make_shared<EventManager>();
    m_Window = std::make_unique<Window>("Engine", 640, 480, this->m_EventManager);
    
    this->MainLoop();
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
    m_Window->Input();
}

void Application::Update(float dt)
{
    m_Window->Update(dt);
}

void Application::Render()
{
    m_Window->Render();
}