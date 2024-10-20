#pragma once

#include "shader.h"
#include "texture2d.h"

#include <map>
#include <string>

#include <sstream>
#include <fstream>

#include <glad/glad.h>


namespace Global
{
    class ResourceManager
    {
    public:
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;

        static void Init();
        static void Shutdown();

        static ResourceManager& GetInstance();

        std::shared_ptr<Shader> LoadShader(const char* v_shader_file, const char* f_shader_file, const char* g_shader_file, const std::string& name);
        std::shared_ptr<Shader> GetShader(const std::string& name);
    
        std::shared_ptr<Texture2D> LoadTexture(const char* file, bool alpha, const std::string& name);
        std::shared_ptr<Texture2D> GetTexture(const std::string& name);

        void Clear();
    private:
        ResourceManager();
        ~ResourceManager();
    private:
        std::shared_ptr<Shader> LoadShaderFromFile(const char* v_shader_file, const char* f_shader_file, const char* g_shader_file = nullptr);
        std::shared_ptr<Texture2D> LoadTextureFromFile(const char* file, bool alpha);
    private:
        // storage
        std::map<std::string, std::shared_ptr<Shader>> m_shaders;
        std::map<std::string, std::shared_ptr<Texture2D>> m_textures;
    };
}
