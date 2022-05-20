#pragma once

#include "buffer.h"
#include "vertex_array.h"
#include "shader.h"
#include "texture2d.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Renderer
{
private:
    Shader shader;
    VertexArray vao;
private:
    void init_data();
public:
    Renderer(Shader& shader);
    ~Renderer();

    void draw_sprite(glm::vec2 position, glm::vec2 size = glm::vec2(10.f, 10.f), 
                        float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
};