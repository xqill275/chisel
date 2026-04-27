#pragma once

/**
 * @file renderer.h
 * @brief 2D sprite renderer.
 */

#include "chisel/shader.h"
#include "chisel/texture.h"
#include "chisel/camera.h"

namespace chisel {

/**
 * @brief A 2D sprite renderer.
 *
 * Draws textured quads to the screen. Create one instance and use it
 * for all drawing in your game loop. Call begin() before drawing and
 * end() after.
 *
 * Pass a Camera to begin() to apply pan and zoom. Without a camera the
 * view is fixed with (0,0) at the top-left of the window.
 *
 * ### Usage — with camera
 * @code
 * chisel::Camera   camera(1280, 720);
 * chisel::Renderer renderer(1280, 720);
 *
 * camera.setPosition(playerX, playerY);
 *
 * renderer.begin(camera);
 * renderer.drawSprite(texture, x, y, 64.0f, 64.0f);
 * renderer.end();
 * window.swapBuffers();
 * @endcode
 *
 * ### Usage — without camera
 * @code
 * renderer.begin();
 * renderer.drawSprite(texture, 100.0f, 100.0f, 64.0f, 64.0f);
 * renderer.end();
 * @endcode
 */
class Renderer {
public:
    /**
     * @brief Creates the renderer and sets up the default projection.
     * @param viewportWidth  Width of the viewport in pixels.
     * @param viewportHeight Height of the viewport in pixels.
     */
    Renderer(int viewportWidth, int viewportHeight);

    /**
     * @brief Frees GPU resources.
     */
    ~Renderer();

    Renderer(const Renderer&)            = delete;
    Renderer& operator=(const Renderer&) = delete;

    /**
     * @brief Begins a new frame using a camera for the view.
     * @param camera The camera to use for this frame.
     * @param r Red   clear colour (0–1).
     * @param g Green clear colour (0–1).
     * @param b Blue  clear colour (0–1).
     */
    void begin(const Camera& camera,
               float r = 0.1f, float g = 0.1f, float b = 0.2f);

    /**
     * @brief Begins a new frame with a fixed view — (0,0) top-left.
     * @param r Red   clear colour (0–1).
     * @param g Green clear colour (0–1).
     * @param b Blue  clear colour (0–1).
     */
    void begin(float r = 0.1f, float g = 0.1f, float b = 0.2f);

    /**
     * @brief Ends the current frame.
     */
    void end();

    /**
     * @brief Draws a textured sprite.
     * @param texture  The texture to draw.
     * @param x        Top-left X position in world space.
     * @param y        Top-left Y position in world space.
     * @param width    Width in pixels.
     * @param height   Height in pixels.
     * @param rotation Clockwise rotation in degrees.
     * @param r        Tint red   (0–1).
     * @param g        Tint green (0–1).
     * @param b        Tint blue  (0–1).
     * @param a        Tint alpha (0–1).
     */
    void drawSprite(const Texture& texture,
                    float x, float y,
                    float width, float height,
                    float rotation = 0.0f,
                    float r = 1.0f, float g = 1.0f,
                    float b = 1.0f, float a = 1.0f);

    /**
     * @brief Updates the projection when the viewport is resized.
     */
    void resize(int width, int height);

private:
    Shader       m_shader;
    unsigned int m_vao         = 0;
    unsigned int m_vbo         = 0;
    float        m_projection[16] = {};

    void buildProjection(int width, int height);
    void drawSpriteInternal(const Texture& texture,
                            float x, float y,
                            float width, float height,
                            float rotation,
                            float r, float g, float b, float a,
                            const float* projection);
};

} // namespace chisel