#include "chisel/input.h"

#include <GLFW/glfw3.h>

namespace chisel {

// Static storage 
bool   Input::s_keyDown[KEY_COUNT]       = {};
bool   Input::s_keyPressed[KEY_COUNT]    = {};
bool   Input::s_keyReleased[KEY_COUNT]   = {};

bool   Input::s_mouseDown[MOUSE_COUNT]    = {};
bool   Input::s_mousePressed[MOUSE_COUNT] = {};
bool   Input::s_mouseReleased[MOUSE_COUNT]= {};

double Input::s_mouseX = 0.0;
double Input::s_mouseY = 0.0;

// Keyboard 

bool Input::isKeyDown(Key key) {
    int k = static_cast<int>(key);
    if (k < 0 || k >= KEY_COUNT) return false;
    return s_keyDown[k];
}

bool Input::isKeyPressed(Key key) {
    int k = static_cast<int>(key);
    if (k < 0 || k >= KEY_COUNT) return false;
    return s_keyPressed[k];
}

bool Input::isKeyReleased(Key key) {
    int k = static_cast<int>(key);
    if (k < 0 || k >= KEY_COUNT) return false;
    return s_keyReleased[k];
}

// Mouse 

bool Input::isMouseButtonDown(MouseButton button) {
    int b = static_cast<int>(button);
    if (b < 0 || b >= MOUSE_COUNT) return false;
    return s_mouseDown[b];
}

bool Input::isMouseButtonPressed(MouseButton button) {
    int b = static_cast<int>(button);
    if (b < 0 || b >= MOUSE_COUNT) return false;
    return s_mousePressed[b];
}

bool Input::isMouseButtonReleased(MouseButton button) {
    int b = static_cast<int>(button);
    if (b < 0 || b >= MOUSE_COUNT) return false;
    return s_mouseReleased[b];
}

void Input::mousePosition(double& x, double& y) {
    x = s_mouseX;
    y = s_mouseY;
}

// Internal callbacks — fed by Window 

void Input::onKey(int key, int action) {
    if (key < 0 || key >= KEY_COUNT) return;

    if (action == GLFW_PRESS) {
        s_keyDown[key]    = true;
        s_keyPressed[key] = true;
    } else if (action == GLFW_RELEASE) {
        s_keyDown[key]     = false;
        s_keyReleased[key] = true;
    }
}

void Input::onMouseButton(int button, int action) {
    if (button < 0 || button >= MOUSE_COUNT) return;

    if (action == GLFW_PRESS) {
        s_mouseDown[button]    = true;
        s_mousePressed[button] = true;
    } else if (action == GLFW_RELEASE) {
        s_mouseDown[button]     = false;
        s_mouseReleased[button] = true;
    }
}

void Input::onMouseMove(double x, double y) {
    s_mouseX = x;
    s_mouseY = y;
}

// End of frame — clears single-frame states 

void Input::endFrame() {
    for (int i = 0; i < KEY_COUNT; ++i) {
        s_keyPressed[i]  = false;
        s_keyReleased[i] = false;
    }
    for (int i = 0; i < MOUSE_COUNT; ++i) {
        s_mousePressed[i]  = false;
        s_mouseReleased[i] = false;
    }
}

} // namespace chisel