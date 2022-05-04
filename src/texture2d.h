#pragma once

#include <glad/glad.h>


class Texture2D
{
public:
    unsigned int m_id;
    unsigned int m_width;
    unsigned int m_height;

    unsigned int m_internal_format;
    unsigned int m_image_format;
    unsigned int m_wrap_s;
    unsigned int m_wrap_t;

    unsigned int m_filter_min;
    unsigned int m_filter_max;
public:
    Texture2D();
    ~Texture2D() = default;

    void generate(unsigned int width, unsigned int height, unsigned char* data);
    void bind() const;
};