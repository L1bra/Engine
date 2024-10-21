#pragma once

#include "Buffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture2d.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void DrawSprite(glm::vec2 position, glm::vec2 size = glm::vec2(10.f, 10.f), 
                        float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f)/*, Shader& shader*/);
private:
    void InitData();
private:
    std::shared_ptr<Shader> shader;
    VertexArray vao;
};