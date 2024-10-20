#pragma once

#include "window.h"
#include "input_handler.h"
#include "Events/event_manager.h"


struct ApplicationContext
{
    std::shared_ptr<IEventManager> m_EventManager;
    //std::unique_ptr<InputHandler> m_Input_handler;
    //std::unique_ptr<Window> m_Window;

    ApplicationContext()
        :
        m_EventManager(std::make_shared<EventManager>())
    {

    }


};


class Application : public EventListener
{
public:
    Application(std::shared_ptr<IEventManager> EventManager);
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

    void Close();

private:
    bool OnWindowResize(int width, int height);
    bool OnWindowClose();
private:
    bool m_Running = true;
    bool m_Minimized = false;

    std::shared_ptr<IEventManager> m_EventManager;

    std::unique_ptr<InputHandler> m_Input_handler;
    std::unique_ptr<Window> m_Window;
};