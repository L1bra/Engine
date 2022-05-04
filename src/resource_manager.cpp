#include "resource_manager.h"

extern "C" {
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
}

std::map<std::string, Shader*> ResourceManager::m_shaders;
std::map<std::string, Texture2D*> ResourceManager::m_textures;

Shader* ResourceManager::load_shader(const char* v_shader_file, const char* f_shader_file, const char* g_shader_file, const std::string& name)
{
    Shader* shader = load_shader_from_file(v_shader_file, f_shader_file, g_shader_file);
    m_shaders[name] = shader;
    return shader;
}

Shader* ResourceManager::get_shader(const std::string& name)
{
    return m_shaders[name];
}

Texture2D* ResourceManager::load_texture(const char* file, bool alpha, const std::string& name)
{
    Texture2D* texture = load_texture_from_file(file, alpha); 
    m_textures[name] = texture;
    return texture;
}

Texture2D* ResourceManager::get_texture(const std::string& name)
{
    return m_textures[name];
}

void ResourceManager::clear()
{
    for(auto& it : m_shaders)
        glDeleteProgram(it.second->m_id);
    
    for(auto& it : m_textures)
        glDeleteTextures(1, (const GLuint*)it.second->m_id);
}

Shader* ResourceManager::load_shader_from_file(const char* v_shader_file, const char* f_shader_file, const char* g_shader_file)
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
    
    Shader* shader = new Shader();
    shader->compile(v_shader_code, f_shader_code, g_shader_file != nullptr ? g_shader_code : nullptr);
    return shader;
}

Texture2D* ResourceManager::load_texture_from_file(const char* file, bool alpha)
{
    Texture2D* texture = new Texture2D();
    if(alpha)
    {
        texture->m_internal_format = GL_RGBA;
        texture->m_image_format = GL_RGBA;
    }

    int width;
    int height;
    int channels;
    unsigned char* data = stbi_load(file, &width, &height, &channels, 0);
    if(!data)
        printf("data is nullptr\n");

    texture->generate(width, height, data);

    stbi_image_free(data);
    return texture;
}