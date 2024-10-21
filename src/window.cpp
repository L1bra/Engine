#include "Window.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include <cassert>


Window::Window(std::shared_ptr<IEventManager> EventManager)
    :
    EventListener(EventManager),
    m_Name("title"),
    m_Width(640),
    m_Height(480),
    m_EventManager(EventManager),
    m_Input_handler(std::make_unique<InputHandler>(this->m_EventManager))
{
    Init("title", 640, 480);
}

Window::Window(const std::string& name, uint16_t width, uint16_t height, std::shared_ptr<IEventManager> EventManager)
    :
    EventListener(EventManager),
    m_Name(name),
    m_Width(width),
    m_Height(height),
    m_EventManager(EventManager),
    m_Input_handler(std::make_unique<InputHandler>(this->m_EventManager))
{
    Init(name, width, height);
}

Window::~Window()
{
}

void Window::Init(const std::string& name, uint16_t width, uint16_t height)
{    
    // setup systems
    assert(this->m_EventManager);
    assert(this->m_Input_handler);

    // setup window
    this->m_Name = name;
    this->m_Width = width;
    this->m_Height = height;

    if(!glfwInit())
    {
        printf("ERROR: glfwInit() failed!\n");
        Close();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_GLFW_Window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if(!m_GLFW_Window)
    {
        printf("ERROR: glfwCreateWindow() failed!\n");
        Close();
    }

    m_GraphicsContext = new OpenGLContext(m_GLFW_Window);
    m_GraphicsContext->Init();

    m_Renderer = std::make_shared<Renderer>(); // TODO: Rendering Context

    glfwSetWindowUserPointer(m_GLFW_Window, this);
    glfwSetCursorPosCallback(m_GLFW_Window, mouse_moved_callback);
    glfwSetScrollCallback(m_GLFW_Window, mouse_scrolled_callback);
    glfwSetMouseButtonCallback(m_GLFW_Window, mouse_button_callback);
    glfwSetKeyCallback(m_GLFW_Window, key_callback);
    glfwSetWindowSizeCallback(m_GLFW_Window, window_resized_callback);
    glfwSetWindowCloseCallback(m_GLFW_Window, window_closed_callback);
    glfwSetWindowRefreshCallback(m_GLFW_Window, window_refresh_callback);
    glfwSetFramebufferSizeCallback(m_GLFW_Window, framebuffer_size_callback);
}

void Window::Input()
{
    if (m_Input_handler->is_key_down(InputHandler::Key::ENTER)) printf("Enter is pressed!\n");
    if (m_Input_handler->is_key_down(InputHandler::Key::ESC)) printf("ESC is pressed!\n");
    if (m_Input_handler->is_key_pressed(InputHandler::Key::W)) printf("W is pressed!\n");
    if (m_Input_handler->is_key_pressed(InputHandler::Key::A)) printf("A is pressed!\n");
    if (m_Input_handler->is_key_pressed(InputHandler::Key::S)) printf("S is pressed!\n");
    if (m_Input_handler->is_key_pressed(InputHandler::Key::D)) printf("D is pressed!\n");
}

void Window::Update(float dt)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_Input_handler->update();

    m_EventManager->process_events();
    glfwPollEvents();
}

void Window::Render()
{
    this->m_Renderer->DrawSprite(glm::vec2(0.5f, 0.0f));
    this->m_GraphicsContext->SwapBuffers();
}

void Window::Render(Renderer& renderer)
{
    renderer.DrawSprite(glm::vec2(0.5f, 0.0f));
    this->m_GraphicsContext->SwapBuffers();
}

bool Window::IsOpen() const
{
    return !glfwWindowShouldClose(m_GLFW_Window);
}

void Window::Close()
{
    glfwDestroyWindow(m_GLFW_Window);
}

void Window::window_resized_callback(GLFWwindow* window, int width, int height)
{
    auto& handle = *(Window*)glfwGetWindowUserPointer(window);
    handle.m_EventManager->queue_event(std::shared_ptr<IEvent>(new WindowResizeEvent(width, height)));
}

void Window::window_closed_callback(GLFWwindow* window)
{
    auto& handle = *(Window*)glfwGetWindowUserPointer(window);
    handle.m_EventManager->queue_event(std::shared_ptr<IEvent>(new WindowCloseEvent()));
}

void Window::mouse_moved_callback(GLFWwindow* window, double x, double y)
{
    auto& handle = *(Window*)glfwGetWindowUserPointer(window);
    handle.m_EventManager->queue_event(std::shared_ptr<IEvent>(new MouseMovedEvent(x, y)));
}

void Window::mouse_scrolled_callback(GLFWwindow* window, double x, double y)
{
    auto& handle = *(Window*)glfwGetWindowUserPointer(window);
    handle.m_EventManager->queue_event(std::shared_ptr<IEvent>(new MouseScrolledEvent(x, y)));
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    auto& handle = *(Window*)glfwGetWindowUserPointer(window);
    if(action == GLFW_PRESS)
    {
        handle.m_EventManager->queue_event(std::shared_ptr<IEvent>(new MouseButtonPressedEvent(button)));
    }
    else if(action == GLFW_RELEASE)
    {
        handle.m_EventManager->queue_event(std::shared_ptr<IEvent>(new MouseButtonReleasedEvent(button)));
    }
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto& handle = *(Window*)glfwGetWindowUserPointer(window);
    switch(action)
    {
        case GLFW_PRESS:
        {
            handle.m_EventManager->queue_event(std::shared_ptr<IEvent>(new KeyPressedEvent(key, scancode, action, mods)));
        } break;

        case GLFW_RELEASE:
        {
            handle.m_EventManager->queue_event(std::shared_ptr<IEvent>(new KeyReleasedEvent(key, scancode, action, mods)));
        } break;
    }
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::window_refresh_callback(GLFWwindow* window)
{
    auto& handle = *(Window*)glfwGetWindowUserPointer(window);
    handle.Render();

    //glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glFinish();
}
