#pragma once

/**
 * @file camera.h
 * @brief 2D orthographic camera with pan and zoom.
 */

namespace chisel {

/**
 * @brief A 2D orthographic camera.
 *
 * Controls what part of the game world is visible. Move it to pan the view,
 * adjust zoom to scale in and out. Pass it to Renderer::begin() each frame.
 *
 * Coordinates are in world space — the camera position is the point in the
 * world that maps to the centre of the screen.
 *
 * ### Usage
 * @code
 * chisel::Camera camera(1280, 720);
 * camera.setPosition(playerX, playerY); // follow the player
 * camera.setZoom(2.0f);                 // zoom in 2x
 *
 * renderer.begin(camera);
 * renderer.drawSprite(texture, x, y, 64.0f, 64.0f);
 * renderer.end();
 * @endcode
 */
class Camera {
public:
    /**
     * @brief Creates a camera for the given viewport size.
     * @param viewportWidth  Width of the viewport in pixels.
     * @param viewportHeight Height of the viewport in pixels.
     */
    Camera(int viewportWidth, int viewportHeight);

    /**
     * @brief Sets the world position the camera looks at (centre of screen).
     * @param x Horizontal position in world space.
     * @param y Vertical position in world space.
     */
    void setPosition(float x, float y);

    /**
     * @brief Moves the camera by a given offset.
     * @param dx Horizontal delta in world space.
     * @param dy Vertical delta in world space.
     */
    void move(float dx, float dy);

    /**
     * @brief Sets the zoom level.
     * @param zoom 1.0 = normal, 2.0 = zoomed in 2x, 0.5 = zoomed out 2x.
     */
    void setZoom(float zoom);

    /**
     * @brief Adjusts zoom by a multiplier.
     * @param factor Multiply current zoom by this value.
     */
    void zoomBy(float factor);

    float posX() const { return m_x;    } ///< Current camera X position.
    float posY() const { return m_y;    } ///< Current camera Y position.
    float zoom() const { return m_zoom; } ///< Current zoom level.

    /**
     * @brief Returns a pointer to the 16-float column-major view-projection matrix.
     *
     * Used internally by the Renderer — you don't normally need to call this.
     */
    const float* viewProjection() const { return m_vp; }

    /**
     * @brief Rebuilds the view-projection matrix after viewport resize.
     * @param width  New viewport width in pixels.
     * @param height New viewport height in pixels.
     */
    void resize(int width, int height);

private:
    float m_x    = 0.0f;
    float m_y    = 0.0f;
    float m_zoom = 1.0f;
    int   m_viewportWidth  = 0;
    int   m_viewportHeight = 0;

    float m_vp[16] = {};

    void recalculate();
};

} // namespace chisel