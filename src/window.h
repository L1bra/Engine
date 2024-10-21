#pragma once

#include "ResourceManager.h"
#include "Renderer/Renderer.h"
#include "Renderer/GraphicsContext.h"
#include "InputHandler.h"

#include "Events/EventManager.h"
#include "Events/WindowEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>


class Renderer;


class Window : public EventListener
{
public:
    Window(std::shared_ptr<IEventManager> EventManager);
    Window(const std::string& name, uint16_t width, uint16_t height, std::shared_ptr<IEventManager> EventManager);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    void Init(const std::string& name, uint16_t width, uint16_t height);

    void Input();
    void Update(float dt);
    void Render();
    void Render(Renderer& renderer);

    bool IsOpen() const;
    void Close();
    GLFWwindow* GetWindow() { return m_GLFW_Window; }

    static void window_resized_callback(GLFWwindow* window, int width, int height);
    static void window_closed_callback(GLFWwindow* window);
    static void mouse_moved_callback(GLFWwindow* window, double x, double y);
    static void mouse_scrolled_callback(GLFWwindow* window, double x, double y);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void window_refresh_callback(GLFWwindow* window);
private:
    std::string m_Name;
    uint16_t m_Width;
    uint16_t m_Height;

    std::shared_ptr<IEventManager> m_EventManager;
    std::unique_ptr<InputHandler> m_Input_handler;

    GLFWwindow* m_GLFW_Window;
    GraphicsContext* m_GraphicsContext;
    std::shared_ptr<Renderer> m_Renderer;
};