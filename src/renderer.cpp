#include "renderer.h"

Renderer::Renderer(Shader& shader)
    :
    shader(shader)
{
    init_data();
}

Renderer::~Renderer()
{
    
}

void Renderer::draw_sprite(glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
    (void)position;
    shader.use();
    
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao.unbind();
}

void Renderer::init_data()
{
    float vertices[] = 
    {
        // pos    
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f
    };
    
    vao.bind();

    VertexBuffer vbo(vertices, sizeof(vertices));    
    vbo.bind();

    vbo.unbind();
    vao.unbind();
}