#pragma once

#include "shader.h"
#include "texture2d.h"

#include <map>
#include <string>

#include <sstream>
#include <fstream>

#include <glad/glad.h>

// TODO: memory management
class ResourceManager
{
private:
public:
    // A static singleton class so we delete default constructor obviously..
    ResourceManager() = delete;

    // storage
    static std::map<std::string, Shader*> m_shaders;
    static std::map<std::string, Texture2D*> m_textures;

    static Shader* load_shader(const char* v_shader_file, const char* f_shader_file, const char* g_shader_file, const std::string& name);
    static Shader* get_shader(const std::string& name);
    
    static Texture2D* load_texture(const char* file, bool alpha, const std::string& name);
    static Texture2D* get_texture(const std::string& name);

    static void clear();
private:
    static Shader* load_shader_from_file(const char* v_shader_file, const char* f_shader_file, const char* g_shader_file = nullptr);
    static Texture2D* load_texture_from_file(const char* file, bool alpha);

};