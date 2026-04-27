#pragma once

#include <string>
#include <functional>

/**
 * @file window.h
 * @brief Window creation and management.
 */

namespace chisel {

/**
 * @brief Configuration for a Chisel window.
 *
 * Pass this to the Window constructor to control how the window
 * is created. All fields have sensible defaults so you only need
 * to set what you want to change.
 *
 * @code
 * chisel::WindowConfig cfg;
 * cfg.width = 1920;
 * cfg.height = 1080;
 * cfg.title = "My Game";
 * chisel::Window window(cfg);
 * @endcode
 */
struct WindowConfig {
    int         width     = 1280;            ///< Width of the window in pixels.
    int         height    = 720;             ///< Height of the window in pixels.
    std::string title     = "Chisel Window"; ///< Text shown in the title bar.
    bool        resizable = true;            ///< Whether the user can resize the window.
    bool        vsync     = true;            ///< Reserved for when a renderer is attached.
};

/**
 * @brief A native desktop window.
 *
 * Window is the entry point for any Chisel application. Create one,
 * then drive your game loop either manually or via run().
 *
 * Windows are non-copyable but movable. Only one window per application
 * is supported in v0.1.
 *
 * ### Manual loop
 * @code
 * chisel::Window window(cfg);
 *
 * while (!window.shouldClose()) {
 *     window.pollEvents();
 *     // update and render here
 * }
 * @endcode
 *
 * ### Engine-driven loop
 * @code
 * window.run([&]() -> bool {
 *     // update and render here
 *     return true; // return false to quit
 * });
 * @endcode
 */
class Window {
public:
    /**
     * @brief Creates and displays a window.
     * @param config Window settings. Uses defaults if not provided.
     * @throws std::runtime_error if GLFW fails to initialise or the window cannot be created.
     */
    explicit Window(const WindowConfig& config = {});

    /**
     * @brief Destroys the window and cleans up GLFW.
     */
    ~Window();

    /// Windows cannot be copied.
    Window(const Window&)            = delete;
    /// Windows cannot be copy-assigned.
    Window& operator=(const Window&) = delete;

    /// Windows can be moved.
    Window(Window&&)                 noexcept;
    /// Windows can be move-assigned.
    Window& operator=(Window&&)      noexcept;

    /**
     * @brief Returns true if the user has requested the window to close.
     *
     * Check this at the top of your game loop. It becomes true when the
     * user clicks the close button or presses Alt+F4.
     */
    bool shouldClose() const;

    /**
     * @brief Processes pending OS events.
     *
     * Call this once per frame. Handles input events, resize events,
     * and anything else the OS needs to deliver to your window.
     */
    void pollEvents();

    /**
     * @brief Presents the rendered frame to the screen.
     *
     * No-op in v0.1 — will swap the OpenGL/Vulkan framebuffer once
     * a renderer is attached in v0.3.
     */
    void swapBuffers();

    /**
     * @brief Runs the main game loop.
     *
     * Calls pollEvents() and swapBuffers() each frame, invoking
     * @p onFrame in between. The loop exits when shouldClose() returns
     * true or when @p onFrame returns false.
     *
     * @param onFrame Optional callback invoked every frame.
     *                Return false to exit the loop early.
     */
    void run(const std::function<bool()>& onFrame = nullptr);

    /**
     * @brief Returns the current width of the window framebuffer in pixels.
     *
     * This may differ from the WindowConfig width on HiDPI / Retina displays.
     */
    int width() const;

    /**
     * @brief Returns the current height of the window framebuffer in pixels.
     *
     * This may differ from the WindowConfig height on HiDPI / Retina displays.
     */
    int height() const;

    /**
     * @brief Updates the text shown in the window title bar.
     * @param title The new title string.
     */
    void setTitle(const std::string& title);

private:
    struct Impl;
    Impl* m_impl = nullptr;
};

} // namespace chisel