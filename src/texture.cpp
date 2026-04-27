#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "chisel/texture.h"

#include <glad/glad.h>
#include <stdexcept>

namespace chisel {

Texture::Texture(const std::string& path) {
    // OpenGL expects textures flipped vertically relative to stb's default
    stbi_set_flip_vertically_on_load(true);

    int channels;
    unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &channels, 0);

    if (!data)
        throw std::runtime_error("chisel::Texture: failed to load: " + path);

    // Pick the right format based on how many channels the image has
    GLenum format = GL_RGB;
    if (channels == 4) format = GL_RGBA;
    else if (channels == 1) format = GL_RED;

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    // Upload to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height,
                 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Wrapping — clamp to edge so sprites don't bleed
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Filtering — nearest for pixel art, linear for smooth sprites
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
}

Texture::~Texture() {
    if (m_id)
        glDeleteTextures(1, &m_id);
}

Texture::Texture(Texture&& other) noexcept
    : m_id(other.m_id), m_width(other.m_width), m_height(other.m_height)
{
    other.m_id = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept {
    if (this != &other) {
        if (m_id) glDeleteTextures(1, &m_id);
        m_id     = other.m_id;
        m_width  = other.m_width;
        m_height = other.m_height;
        other.m_id = 0;
    }
    return *this;
}

void Texture::bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace chisel