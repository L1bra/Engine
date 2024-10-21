#pragma once

#include "Window.h"
#include "Events/EventManager.h"


class Application
{
public:
    Application();
    ~Application();
    
    // load application stuff and init systems
    void OnInit();

    // shutdown
    void OnShutdown();

    // main loop
    void MainLoop();

    // input -> update -> render
    void Input();
    void Update(float dt);
    void Render();
private:
    bool m_Running = true;

    std::shared_ptr<IEventManager> m_EventManager;
    std::unique_ptr<Window> m_Window;
};