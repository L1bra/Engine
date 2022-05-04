#include "shader.h"

#include <iostream>


Shader& Shader::use()
{
    glUseProgram(m_id);
    return *this;
}

void Shader::compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
    unsigned int sVertex = 0;
    unsigned int sFragment = 0;
    unsigned int gShader = 0;
    // vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    check_compile_errors(sVertex, "VERTEX");
    // fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    check_compile_errors(sFragment, "FRAGMENT");
    // if geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        check_compile_errors(gShader, "GEOMETRY");
    }
    // shader program
    m_id = glCreateProgram();
    glAttachShader(m_id, sVertex);
    glAttachShader(m_id, sFragment);
    if (geometrySource != nullptr) 
        glAttachShader(m_id, gShader);
    glLinkProgram(m_id);
    check_compile_errors(m_id, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(gShader);
}

void Shader::set_float(const char *name, float value, bool use_shader)
{
    if (use_shader)
        use();
    glUniform1f(glGetUniformLocation(m_id, name), value);
}

void Shader::set_int(const char *name, int value, bool use_shader)
{
    if (use_shader)
        use();
    glUniform1i(glGetUniformLocation(m_id, name), value);
}

void Shader::set_vector2f(const char *name, float x, float y, bool use_shader)
{
    if (use_shader)
        use();
    glUniform2f(glGetUniformLocation(m_id, name), x, y);
}

void Shader::set_vector2f(const char *name, const glm::vec2 &value, bool use_shader)
{
    if (use_shader)
        use();
    glUniform2f(glGetUniformLocation(m_id, name), value.x, value.y);
}

void Shader::set_vector3f(const char *name, float x, float y, float z, bool use_shader)
{
    if (use_shader)
        use();
    glUniform3f(glGetUniformLocation(m_id, name), x, y, z);
}

void Shader::set_vector3f(const char *name, const glm::vec3 &value, bool use_shader)
{
    if (use_shader)
        use();
    glUniform3f(glGetUniformLocation(m_id, name), value.x, value.y, value.z);
}

void Shader::set_vector4f(const char *name, float x, float y, float z, float w, bool use_shader)
{
    if (use_shader)
        use();
    glUniform4f(glGetUniformLocation(m_id, name), x, y, z, w);
}

void Shader::set_vector4f(const char *name, const glm::vec4 &value, bool use_shader)
{
    if (use_shader)
        use();
    glUniform4f(glGetUniformLocation(m_id, name), value.x, value.y, value.z, value.w);
}

void Shader::set_matrix4(const char *name, const glm::mat4 &matrix, bool use_shader)
{
    if (use_shader)
        use();
    glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, false, glm::value_ptr(matrix));
}


void Shader::check_compile_errors(unsigned int object, const char* type)
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