#pragma once

/**
 * @file texture.h
 * @brief 2D texture loading and binding.
 */

#include <string>

namespace chisel {

/**
 * @brief A 2D texture loaded from disk and uploaded to the GPU.
 *
 * Supports PNG and JPG. The texture is uploaded to the GPU on construction
 * and freed on destruction.
 *
 * ### Usage
 * @code
 * chisel::Texture texture("assets/sprites/player.png");
 * texture.bind(); // binds to slot 0 by default
 * @endcode
 */
class Texture {
public:
    /**
     * @brief Loads an image from disk and uploads it to the GPU.
     * @param path Path to the image file (PNG or JPG).
     * @throws std::runtime_error if the file cannot be loaded.
     */
    explicit Texture(const std::string& path);

    /**
     * @brief Frees the texture from the GPU.
     */
    ~Texture();

    // Non-copyable, movable
    Texture(const Texture&)            = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&&)                 noexcept;
    Texture& operator=(Texture&&)      noexcept;

    /**
     * @brief Binds the texture to the given slot.
     * @param slot Texture unit to bind to (0–15). Defaults to 0.
     */
    void bind(unsigned int slot = 0) const;

    /**
     * @brief Unbinds any texture from the given slot.
     * @param slot Texture unit to unbind. Defaults to 0.
     */
    void unbind(unsigned int slot = 0) const;

    int width()  const { return m_width;  } ///< Width of the texture in pixels.
    int height() const { return m_height; } ///< Height of the texture in pixels.

private:
    unsigned int m_id     = 0;
    int          m_width  = 0;
    int          m_height = 0;
};

} // namespace chisel