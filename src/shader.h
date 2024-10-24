#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader() = default;
    ~Shader() = default;

    // set current shader
    Shader& Use();

    // compile shaders from source
    void Compile(const char* vertex_source, const char* fragment_source, const char* geometry_source = nullptr);

    // utility
    void SetFloat(const char* name, float value, bool use_shader = false);
    void SetInt(const char* name, int value, bool use_shader = false);

    void SetVector2f(const char* name, float x, float y, bool use_shader = false);
    void SetVector2f(const char* name, const glm::vec2& value, bool use_shader = false);

    void SetVector3f(const char* name, float x, float y, float z, bool use_shader = false);
    void SetVector3f(const char* name, const glm::vec3& value, bool use_shader = false);

    void SetVector4f(const char* name, float x, float y, float z, float w, bool use_shader = false);
    void SetVector4f(const char* name, const glm::vec4& value, bool use_shader = false);

    void SetMatrix4(const char* name, const glm::mat4& matrix, bool use_shader = false);
private:
    void CheckCompileErrors(unsigned int object, const char* type);
public:
    unsigned int m_id;
};