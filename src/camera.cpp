#include "chisel/camera.h"

namespace chisel {

Camera::Camera(int viewportWidth, int viewportHeight)
    : m_viewportWidth(viewportWidth)
    , m_viewportHeight(viewportHeight)
{
    recalculate();
}

void Camera::setPosition(float x, float y) {
    m_x = x;
    m_y = y;
    recalculate();
}

void Camera::move(float dx, float dy) {
    m_x += dx;
    m_y += dy;
    recalculate();
}

void Camera::setZoom(float zoom) {
    m_zoom = zoom < 0.01f ? 0.01f : zoom; // clamp to avoid divide-by-zero
    recalculate();
}

void Camera::zoomBy(float factor) {
    setZoom(m_zoom * factor);
}

void Camera::resize(int width, int height) {
    m_viewportWidth  = width;
    m_viewportHeight = height;
    recalculate();
}

// ── View-projection matrix ────────────────────────────────────────────────────
// Combines an orthographic projection with a view transform that:
//   1. Scales by zoom
//   2. Translates so the camera position maps to the centre of the screen

void Camera::recalculate() {
    float hw = (m_viewportWidth  * 0.5f) / m_zoom;
    float hh = (m_viewportHeight * 0.5f) / m_zoom;

    // Visible world bounds
    float l = m_x - hw;
    float r = m_x + hw;
    float t = m_y - hh;
    float b = m_y + hh;
    float zn = -1.0f, zf = 1.0f;

    // Column-major orthographic projection
    m_vp[0]  =  2.0f / (r - l);
    m_vp[1]  =  0.0f;
    m_vp[2]  =  0.0f;
    m_vp[3]  =  0.0f;

    m_vp[4]  =  0.0f;
    m_vp[5]  =  2.0f / (t - b);
    m_vp[6]  =  0.0f;
    m_vp[7]  =  0.0f;

    m_vp[8]  =  0.0f;
    m_vp[9]  =  0.0f;
    m_vp[10] = -2.0f / (zf - zn);
    m_vp[11] =  0.0f;

    m_vp[12] = -(r + l) / (r - l);
    m_vp[13] = -(t + b) / (t - b);
    m_vp[14] = -(zf + zn) / (zf - zn);
    m_vp[15] =  1.0f;
}

} // namespace chisel