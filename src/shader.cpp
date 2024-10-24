#include "Shader.h"

#include <iostream>


Shader& Shader::Use()
{
    glUseProgram(m_id);
    return *this;
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
    unsigned int sVertex = 0;
    unsigned int sFragment = 0;
    unsigned int gShader = 0;

    // vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    CheckCompileErrors(sVertex, "VERTEX");

    // fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    CheckCompileErrors(sFragment, "FRAGMENT");

    // if geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        CheckCompileErrors(gShader, "GEOMETRY");
    }

    // shader program
    m_id = glCreateProgram();
    glAttachShader(m_id, sVertex);
    glAttachShader(m_id, sFragment);
    if (geometrySource != nullptr) 
        glAttachShader(m_id, gShader);
    glLinkProgram(m_id);
    CheckCompileErrors(m_id, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(gShader);
}

void Shader::SetFloat(const char *name, float value, bool use_shader)
{
    if (use_shader)
        this->Use();
    glUniform1f(glGetUniformLocation(m_id, name), value);
}

void Shader::SetInt(const char *name, int value, bool use_shader)
{
    if (use_shader)
        this->Use();
    glUniform1i(glGetUniformLocation(m_id, name), value);
}

void Shader::SetVector2f(const char *name, float x, float y, bool use_shader)
{
    if (use_shader)
        this->Use();
    glUniform2f(glGetUniformLocation(m_id, name), x, y);
}

void Shader::SetVector2f(const char *name, const glm::vec2 &value, bool use_shader)
{
    if (use_shader)
        this->Use();
    glUniform2f(glGetUniformLocation(m_id, name), value.x, value.y);
}

void Shader::SetVector3f(const char *name, float x, float y, float z, bool use_shader)
{
    if (use_shader)
        this->Use();
    glUniform3f(glGetUniformLocation(m_id, name), x, y, z);
}

void Shader::SetVector3f(const char *name, const glm::vec3 &value, bool use_shader)
{
    if (use_shader)
        this->Use();
    glUniform3f(glGetUniformLocation(m_id, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const char *name, float x, float y, float z, float w, bool use_shader)
{
    if (use_shader)
        this->Use();
    glUniform4f(glGetUniformLocation(m_id, name), x, y, z, w);
}

void Shader::SetVector4f(const char *name, const glm::vec4 &value, bool use_shader)
{
    if (use_shader)
        this->Use();
    glUniform4f(glGetUniformLocation(m_id, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const char *name, const glm::mat4 &matrix, bool use_shader)
{
    if (use_shader)
        this->Use();
    glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, false, glm::value_ptr(matrix));
}


void Shader::CheckCompileErrors(unsigned int object, const char* type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}