#include "window.h"

// std::shared_ptr<IEventManager> Window::em;

Window::Window(std::shared_ptr<IEventManager> event_manager)
    :
    name("title"),
    width(640),
    height(480),
    em(event_manager)
{
    init("title", 640, 480);
}

Window::Window(const std::string& name, uint16_t width, uint16_t height, std::shared_ptr<IEventManager> event_manager)
    :
    name(name),
    width(width),
    height(height),
    em(event_manager)
{
    init(name, width, height);
}

Window::~Window()
{
    // em = 0;
}

//TODO: refactor this
void Window::init(const std::string& name, uint16_t width, uint16_t height)
{    
    // setup systems
    if(!em)
    {
        return;
    }
    
    // setup window
    this->name = name;
    this->width = width;
    this->height = height;

    if(!glfwInit())
    {
        printf("ERROR: glfwInit() failed!\n");
        close();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfw_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if(!glfw_window)
    {
        printf("ERROR: glfwCreateWindow() failed!\n");
        close();
    }

    glfwMakeContextCurrent(glfw_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("ERROR: Failed to init GLAD!\n");
        close();
    }

    glfwSetWindowUserPointer(glfw_window, this);
    glfwSetCursorPosCallback(glfw_window, mouse_moved_callback);
    glfwSetScrollCallback(glfw_window, mouse_scrolled_callback);
    glfwSetMouseButtonCallback(glfw_window, mouse_button_callback);
    glfwSetKeyCallback(glfw_window, key_callback);
    glfwSetWindowSizeCallback(glfw_window, window_resized_callback);
    glfwSetWindowCloseCallback(glfw_window, window_closed_callback);
}

void Window::update()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwPollEvents();
    em->process_events();
}

void Window::render(Renderer& renderer)
{
    renderer.draw_sprite(glm::vec2(0.5f, 0.0f));
    glfwSwapBuffers(glfw_window);
}

bool Window::is_open() const
{
    return !glfwWindowShouldClose(glfw_window);
}

void Window::close()
{
    glfwDestroyWindow(glfw_window);
}

void Window::window_resized_callback(GLFWwindow* window, int width, int height)
{
    auto& handle = *(Window*)glfwGetWindowUserPointer(window);
    handle.em->queue_event(std::shared_ptr<IEvent>(new WindowResizedEvent(width, height)));
}

void Window::window_closed_callback(GLFWwindow* window)
{
    auto& handle = *(Window*)glfwGetWindowUserPointer(window);
    handle.em->queue_event(std::shared_ptr<IEvent>(new WindowClosedEvent()));
}

void Window::mouse_moved_callback(GLFWwindow* window, double x, double y)
{
    auto& handle = *(Window*)glfwGetWindowUserPointer(window);
    handle.em->queue_event(std::shared_ptr<IEvent>(new MouseMovedEvent(x, y)));
}

void Window::mouse_scrolled_callback(GLFWwindow* window, double x, double y)
{
    auto& handle = *(Window*)glfwGetWindowUserPointer(window);
    handle.em->queue_event(std::shared_ptr<IEvent>(new MouseScrolledEvent(x, y)));
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        handle.em->queue_event(std::shared_ptr<IEvent>(new MouseButtonPressedEvent(button)));
    }
    else
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        handle.em->queue_event(std::shared_ptr<IEvent>(new MouseButtonReleasedEvent(button)));
    }
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        handle.em->queue_event(std::shared_ptr<IEvent>(new KeyPressedEvent(key)));
    }
    else
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        handle.em->queue_event(std::shared_ptr<IEvent>(new KeyReleasedEvent(key)));
    }
}