#include "renderer.h"

Renderer::Renderer(Shader* shader)
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
    shader->use();
    
    glBindVertexArray(quad_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Renderer::init_data()
{
    unsigned int vbo;

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
    
    glGenVertexArrays(1, &quad_vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(quad_vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}