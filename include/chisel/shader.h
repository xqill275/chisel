#pragma once

/**
 * @file shader.h
 * @brief GLSL shader program loading and uniform management.
 */

#include <string>

namespace chisel {

/**
 * @brief A compiled and linked GLSL shader program.
 *
 * Loads a vertex and fragment shader from disk, compiles them,
 * and links them into a program ready for use in draw calls.
 *
 * ### Usage
 * @code
 * chisel::Shader shader("assets/shaders/sprite.vert",
 *                       "assets/shaders/sprite.frag");
 *
 * shader.bind();
 * shader.setMat4("projection", projMatrix);
 * shader.setVec4("colour", 1.0f, 1.0f, 1.0f, 1.0f);
 * @endcode
 */
class Shader {
public:
    /**
     * @brief Loads, compiles, and links a shader program from two GLSL source files.
     * @param vertexPath   Path to the vertex shader source file.
     * @param fragmentPath Path to the fragment shader source file.
     * @throws std::runtime_error if a file cannot be read or compilation fails.
     */
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    /**
     * @brief Deletes the shader program from the GPU.
     */
    ~Shader();

    // Non-copyable, movable
    Shader(const Shader&)            = delete;
    Shader& operator=(const Shader&) = delete;
    Shader(Shader&&)                 noexcept;
    Shader& operator=(Shader&&)      noexcept;

    /**
     * @brief Binds this shader program for subsequent draw calls.
     */
    void bind() const;

    /**
     * @brief Unbinds any active shader program.
     */
    void unbind() const;

    // ── Uniform setters ───────────────────────────────────────────────────────

    /// Sets a single integer uniform (also used for sampler2D texture slots).
    void setInt  (const std::string& name, int value)                              const;
    /// Sets a single float uniform.
    void setFloat(const std::string& name, float value)                            const;
    /// Sets a vec2 uniform.
    void setVec2 (const std::string& name, float x, float y)                      const;
    /// Sets a vec3 uniform.
    void setVec3 (const std::string& name, float x, float y, float z)             const;
    /// Sets a vec4 uniform.
    void setVec4 (const std::string& name, float x, float y, float z, float w)    const;
    /// Sets a 4x4 matrix uniform. @p matrix should point to 16 floats (column-major).
    void setMat4 (const std::string& name, const float* matrix)                   const;

private:
    unsigned int m_id = 0; ///< OpenGL program handle.

    unsigned int compile(unsigned int type, const std::string& source) const;
    int          getUniformLocation(const std::string& name)           const;
};

} // namespace chisel