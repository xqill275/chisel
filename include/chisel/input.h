#pragma once

/**
 * @file input.h
 * @brief Keyboard and mouse input queries.
 */

namespace chisel {

// Key codes 

/**
 * @brief Keyboard key codes.
 *
 * Use these with chisel::Input::isKeyDown(), isKeyPressed(), and isKeyReleased().
 *
 * @code
 * if (chisel::Input::isKeyDown(chisel::Key::Space)) {
 *     player.jump();
 * }
 * @endcode
 */
enum class Key {
    // Printable
    Space        = 32,
    Apostrophe   = 39,
    Comma        = 44,
    Minus        = 45,
    Period       = 46,
    Slash        = 47,

    Num0 = 48, Num1 = 49, Num2 = 50, Num3 = 51, Num4 = 52,
    Num5 = 53, Num6 = 54, Num7 = 55, Num8 = 56, Num9 = 57,

    A = 65, B = 66, C = 67, D = 68, E = 69, F = 70,
    G = 71, H = 72, I = 73, J = 74, K = 75, L = 76,
    M = 77, N = 78, O = 79, P = 80, Q = 81, R = 82,
    S = 83, T = 84, U = 85, V = 86, W = 87, X = 88,
    Y = 89, Z = 90,

    // Function keys
    Escape    = 256,
    Enter     = 257,
    Tab       = 258,
    Backspace = 259,
    Insert    = 260,
    Delete    = 261,
    Right     = 262,
    Left      = 263,
    Down      = 264,
    Up        = 265,
    PageUp    = 266,
    PageDown  = 267,
    Home      = 268,
    End       = 269,

    F1  = 290, F2  = 291, F3  = 292, F4  = 293,
    F5  = 294, F6  = 295, F7  = 296, F8  = 297,
    F9  = 298, F10 = 299, F11 = 300, F12 = 301,

    // Modifiers
    LeftShift    = 340,
    LeftControl  = 341,
    LeftAlt      = 342,
    RightShift   = 344,
    RightControl = 345,
    RightAlt     = 346,
};

// Mouse buttons 

/**
 * @brief Mouse button codes.
 *
 * Use these with chisel::Input::isMouseButtonDown() and isMouseButtonPressed().
 */
enum class MouseButton {
    Left   = 0,
    Right  = 1,
    Middle = 2,
};

// Input 

/**
 * @brief Static input query interface.
 *
 * Provides per-frame keyboard and mouse state. All methods are static —
 * there is no instance to manage. Input is updated automatically by the
 * Window each frame; you do not need to call anything manually.
 *
 * ### Key state
 * @code
 * // held down — true every frame the key is held
 * if (chisel::Input::isKeyDown(chisel::Key::D)) player.moveRight();
 *
 * // pressed — true only on the first frame the key is held
 * if (chisel::Input::isKeyPressed(chisel::Key::Space)) player.jump();
 *
 * // released — true only on the frame the key is let go
 * if (chisel::Input::isKeyReleased(chisel::Key::Escape)) quit();
 * @endcode
 *
 * ### Mouse state
 * @code
 * auto [x, y] = chisel::Input::mousePosition();
 * if (chisel::Input::isMouseButtonPressed(chisel::MouseButton::Left)) fire();
 * @endcode
 */
class Input {
public:
    Input()                        = delete; ///< Input is a static-only class.

    // Keyboard 

    /**
     * @brief Returns true every frame the key is held down.
     * @param key The key to query.
     */
    static bool isKeyDown(Key key);

    /**
     * @brief Returns true only on the first frame the key is pressed.
     * @param key The key to query.
     */
    static bool isKeyPressed(Key key);

    /**
     * @brief Returns true only on the frame the key is released.
     * @param key The key to query.
     */
    static bool isKeyReleased(Key key);

    // Mouse 

    /**
     * @brief Returns true every frame the mouse button is held down.
     * @param button The button to query.
     */
    static bool isMouseButtonDown(MouseButton button);

    /**
     * @brief Returns true only on the first frame the mouse button is pressed.
     * @param button The button to query.
     */
    static bool isMouseButtonPressed(MouseButton button);

    /**
     * @brief Returns true only on the frame the mouse button is released.
     * @param button The button to query.
     */
    static bool isMouseButtonReleased(MouseButton button);

    /**
     * @brief Returns the current mouse cursor position in screen coordinates.
     * @param x Output — horizontal position in pixels from the left of the window.
     * @param y Output — vertical position in pixels from the top of the window.
     */
    static void mousePosition(double& x, double& y);

    //  Internal — called by Window, not user code 

    /// @private
    static void onKey(int key, int action);
    /// @private
    static void onMouseButton(int button, int action);
    /// @private
    static void onMouseMove(double x, double y);
    /// @private
    static void endFrame();

private:
    static constexpr int KEY_COUNT    = 512;
    static constexpr int MOUSE_COUNT  = 8;

    static bool s_keyDown[KEY_COUNT];
    static bool s_keyPressed[KEY_COUNT];
    static bool s_keyReleased[KEY_COUNT];

    static bool s_mouseDown[MOUSE_COUNT];
    static bool s_mousePressed[MOUSE_COUNT];
    static bool s_mouseReleased[MOUSE_COUNT];

    static double s_mouseX;
    static double s_mouseY;
};

} // namespace chisel