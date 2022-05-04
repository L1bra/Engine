#pragma once

#include "resource_manager.h"
#include "renderer.h"

#include "events/event_manager.h"
#include "events/window_event.h"
#include "events/mouse_event.h"
#include "events/key_event.h"

#include "input_handler.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>


class Window final
{
private:
    std::string name;
    uint16_t width;
    uint16_t height;

    GLFWwindow* glfw_window;
    
    std::shared_ptr<IEventManager> em;
public:
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    Window(std::shared_ptr<IEventManager> event_manager);
    Window(const std::string& name, uint16_t width, uint16_t height, std::shared_ptr<IEventManager> event_manager);
    ~Window();

    void init(const std::string& name, uint16_t width, uint16_t height);

    void update();
    void render(Renderer& renderer);

    bool is_open() const;
    void close();

    static void window_resized_callback(GLFWwindow* window, int width, int height);
    static void window_closed_callback(GLFWwindow* window);
    static void mouse_moved_callback(GLFWwindow* window, double x, double y);
    static void mouse_scrolled_callback(GLFWwindow* window, double x, double y);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};