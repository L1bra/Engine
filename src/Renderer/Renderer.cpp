#include "Renderer/Renderer.h"
#include "ResourceManager.h"

#include "GLFW/glfw3.h"
#include <cmath>

Renderer::Renderer()
{
    InitData();
}

Renderer::~Renderer()
{
}

void Renderer::InitData()
{
    //float vertices[] = {
    //     0.5f,  0.5f, 0.0f,  // top right
    //     0.5f, -0.5f, 0.0f,  // bottom right
    //    -0.5f, -0.5f, 0.0f,  // bottom left
    //    -0.5f,  0.5f, 0.0f   // top left 
    //};


    //unsigned int indices[] = {
    //    0, 1, 3,   // first triangle
    //    1, 2, 3    // second triangle
    //};

    float vertices[] = {
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    m_VAO.bind();

    m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
    m_VBO->Bind();

    //m_IBO.reset(IndexBuffer::Create(indices, 6));
    //m_IBO->Bind();

    m_VBO->Unbind();
    m_VAO.unbind();
    //m_IBO->Unbind();

    // default shader
    Global::ResourceManager::GetInstance().LoadShader("src/Shaders/default.vs", "src/Shaders/default.fs", nullptr, "default");
    Global::ResourceManager::GetInstance().LoadShader("src/Shaders/default.vs", "src/Shaders/flicker.fs", nullptr, "flicker");

    m_Shader = Global::ResourceManager::GetInstance().GetShader("flicker");
    m_Shader->Use();
}

void Renderer::DrawSprite(glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color/*, Shader& shader*/)
{
    return;
}

void Renderer::Draw()
{
    m_VAO.bind();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe mode
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    double TimeValue = glfwGetTime();
    float GreenValue = (std::sin(TimeValue) / 2.0f) + 0.5f;
    m_Shader->SetVector4f("ourColor", glm::vec4{ 0.f, GreenValue, 0.0f, 1.0f });

    glDrawArrays(GL_TRIANGLES, 0, 3);

    m_VAO.unbind();
}
