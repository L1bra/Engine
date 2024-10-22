#include "ResourceManager.h"
#include <cassert>

extern "C" {
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.h"
}

namespace Global
{
    static ResourceManager* s_Instance = nullptr;

    ResourceManager::ResourceManager()
    {
    }

    ResourceManager::~ResourceManager()
    {
        this->Clear();
    }

    void ResourceManager::Init()
    {
        assert(!s_Instance);

        s_Instance = new ResourceManager();
    }

    void ResourceManager::Shutdown()
    {
        delete s_Instance;
        s_Instance = nullptr;
    }

    ResourceManager& ResourceManager::GetInstance()
    {
        assert(s_Instance);
        return *s_Instance;
    }


    std::shared_ptr<Shader> ResourceManager::LoadShader(const char* v_shader_file, const char* f_shader_file, const char* g_shader_file, const std::string& name)
    {
        std::shared_ptr<Shader> shader = LoadShaderFromFile(v_shader_file, f_shader_file, g_shader_file);
        m_shaders[name] = shader;
        return shader;
    }

    std::shared_ptr<Shader> Global::ResourceManager::GetShader(const std::string& name)
    {
        return m_shaders[name];
    }

    std::shared_ptr<Texture2D> Global::ResourceManager::LoadTexture(const char* file, bool alpha, const std::string& name)
    {
        std::shared_ptr<Texture2D> texture = LoadTextureFromFile(file, alpha);
        m_textures[name] = texture;
        return texture;
    }

    std::shared_ptr<Texture2D> Global::ResourceManager::GetTexture(const std::string& name)
    {
        return m_textures[name];
    }

    void Global::ResourceManager::Clear()
    {
        for(auto& it : m_shaders)
            glDeleteProgram(it.second->m_id);
    
        for(auto& it : m_textures)
            glDeleteTextures(1, (const GLuint*)it.second->m_id);
    }

    std::shared_ptr<Shader> Global::ResourceManager::LoadShaderFromFile(const char* v_shader_file, const char* f_shader_file, const char* g_shader_file)
    {
        std::string vertex_code;
        std::string fragment_code;
        std::string geometry_code;

        std::ifstream vertex_shader_file(v_shader_file);
        std::ifstream fragment_shader_file(f_shader_file);
    
        std::stringstream v_shader_stream;
        std::stringstream f_shader_stream;

        v_shader_stream << vertex_shader_file.rdbuf();
        f_shader_stream << fragment_shader_file.rdbuf();

        vertex_shader_file.close();
        fragment_shader_file.close();

        vertex_code = v_shader_stream.str();
        fragment_code = f_shader_stream.str();

        if(g_shader_file)
        {
            std::ifstream geometry_shader_file(g_shader_file);
            std::stringstream g_shader_stream;

            g_shader_stream << geometry_shader_file.rdbuf();
            geometry_shader_file.close();
        
            geometry_code = g_shader_stream.str();
        }

        const char* v_shader_code = vertex_code.c_str();
        const char* f_shader_code = fragment_code.c_str();
        const char* g_shader_code = geometry_code.c_str();
    
        std::shared_ptr<Shader> shader = std::make_shared<Shader>();
        shader->compile(v_shader_code, f_shader_code, g_shader_file != nullptr ? g_shader_code : nullptr);
        return shader;
    }

    std::shared_ptr<Texture2D> Global::ResourceManager::LoadTextureFromFile(const char* file, bool alpha)
    {
        std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>();
        if(alpha)
        {
            texture->m_internal_format = GL_RGBA;
            texture->m_image_format = GL_RGBA;
        }

        int width;
        int height;
        int channels;
        unsigned char* data = stbi_load(file, &width, &height, &channels, 0);

        texture->generate(width, height, data);

        stbi_image_free(data);
        return texture;
    }
}