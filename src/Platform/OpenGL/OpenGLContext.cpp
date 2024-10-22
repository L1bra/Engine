#include "platform/OpenGL/OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cassert>


OpenGLContext::OpenGLContext(GLFWwindow* WindowHandle)
	:
	m_WindowHandle(WindowHandle)
{
    assert(WindowHandle, "WindowHandle is NULL!");
}

void OpenGLContext::Init()
{
    glfwMakeContextCurrent(m_WindowHandle);

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    assert(status, "ERROR: Failed to init GLAD!");
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
    glfwSwapInterval(1);
}
