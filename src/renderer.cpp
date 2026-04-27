#include "chisel/renderer.h"

#include <glad/glad.h>
#include <cmath>

namespace chisel {

// ── Projection ────────────────────────────────────────────────────────────────

void Renderer::buildProjection(int width, int height) {
    float l = 0.0f, r = (float)width;
    float t = 0.0f, b = (float)height;
    float zn = -1.0f, zf = 1.0f;

    m_projection[0]  =  2.0f / (r - l);
    m_projection[1]  =  0.0f;
    m_projection[2]  =  0.0f;
    m_projection[3]  =  0.0f;

    m_projection[4]  =  0.0f;
    m_projection[5]  =  2.0f / (t - b);
    m_projection[6]  =  0.0f;
    m_projection[7]  =  0.0f;

    m_projection[8]  =  0.0f;
    m_projection[9]  =  0.0f;
    m_projection[10] = -2.0f / (zf - zn);
    m_projection[11] =  0.0f;

    m_projection[12] = -(r + l) / (r - l);
    m_projection[13] = -(t + b) / (t - b);
    m_projection[14] = -(zf + zn) / (zf - zn);
    m_projection[15] =  1.0f;
}

// ── Constructor / destructor ──────────────────────────────────────────────────

Renderer::Renderer(int viewportWidth, int viewportHeight)
    : m_shader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag")
{
    buildProjection(viewportWidth, viewportHeight);

    float vertices[] = {
        0.0f, 0.0f,  0.0f, 0.0f,
        1.0f, 0.0f,  1.0f, 0.0f,
        1.0f, 1.0f,  1.0f, 1.0f,

        0.0f, 0.0f,  0.0f, 0.0f,
        1.0f, 1.0f,  1.0f, 1.0f,
        0.0f, 1.0f,  0.0f, 1.0f,
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                          4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                          4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}

// ── Frame control ─────────────────────────────────────────────────────────────

void Renderer::begin(const Camera& camera, float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // Store camera's VP for draw calls this frame
    m_shader.bind();
    m_shader.setMat4("u_projection", camera.viewProjection());
}

void Renderer::begin(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    m_shader.bind();
    m_shader.setMat4("u_projection", m_projection);
}

void Renderer::end() {
    // Reserved for future batching flush
}

// ── Draw ──────────────────────────────────────────────────────────────────────

void Renderer::drawSprite(const Texture& texture,
                           float x, float y,
                           float width, float height,
                           float rotation,
                           float r, float g, float b, float a)
{
    m_shader.setInt ("u_texture", 0);
    m_shader.setVec4("u_colour", r, g, b, a);

    texture.bind(0);

    float cx   = x + width  * 0.5f;
    float cy   = y + height * 0.5f;
    float rad  = rotation * (3.14159265f / 180.0f);
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    float model[16] = {
         cosA * width,  sinA * width,  0.0f, 0.0f,
        -sinA * height, cosA * height, 0.0f, 0.0f,
         0.0f,          0.0f,          1.0f, 0.0f,
         cx - cosA * width * 0.5f + sinA * height * 0.5f,
         cy - sinA * width * 0.5f - cosA * height * 0.5f,
         0.0f, 1.0f
    };

    m_shader.setMat4("u_model", model);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

// ── Resize ────────────────────────────────────────────────────────────────────

void Renderer::resize(int width, int height) {
    glViewport(0, 0, width, height);
    buildProjection(width, height);
}

} // namespace chisel