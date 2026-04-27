#include "chisel/window.h"
#include "chisel/input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace chisel {

// ── PIMPL definition ──────────────────────────────────────────────────────────

struct Window::Impl {
    GLFWwindow* handle = nullptr;

    Impl(const WindowConfig& cfg) {
        if (!glfwInit())
            throw std::runtime_error("chisel: failed to initialise GLFW");

        // Request OpenGL 3.3 core context
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // required on macOS
#endif
        glfwWindowHint(GLFW_RESIZABLE, cfg.resizable ? GLFW_TRUE : GLFW_FALSE);

        handle = glfwCreateWindow(
            cfg.width, cfg.height,
            cfg.title.c_str(),
            nullptr,
            nullptr
        );

        if (!handle) {
            glfwTerminate();
            throw std::runtime_error("chisel: failed to create window");
        }

        glfwMakeContextCurrent(handle);

        // Initialise glad — must happen after context is current
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("chisel: failed to initialise glad");

        // Vsync
        glfwSwapInterval(cfg.vsync ? 1 : 0);

        glfwSetWindowUserPointer(handle, this);

        // Viewport tracks framebuffer size
        glfwSetFramebufferSizeCallback(handle,
            [](GLFWwindow*, int width, int height) {
                glViewport(0, 0, width, height);
            });

        // ── Input callbacks ───────────────────────────────────────────────────

        glfwSetKeyCallback(handle,
            [](GLFWwindow*, int key, int /*scancode*/, int action, int /*mods*/) {
                Input::onKey(key, action);
            });

        glfwSetMouseButtonCallback(handle,
            [](GLFWwindow*, int button, int action, int /*mods*/) {
                Input::onMouseButton(button, action);
            });

        glfwSetCursorPosCallback(handle,
            [](GLFWwindow*, double x, double y) {
                Input::onMouseMove(x, y);
            });

        glfwShowWindow(handle);
        glfwFocusWindow(handle);
    }

    ~Impl() {
        if (handle)
            glfwDestroyWindow(handle);
        glfwTerminate();
    }
};

// ── Window public API ─────────────────────────────────────────────────────────

Window::Window(const WindowConfig& cfg)
    : m_impl(new Impl(cfg))
{}

Window::~Window() {
    delete m_impl;
}

Window::Window(Window&& other) noexcept
    : m_impl(other.m_impl)
{
    other.m_impl = nullptr;
}

Window& Window::operator=(Window&& other) noexcept {
    if (this != &other) {
        delete m_impl;
        m_impl       = other.m_impl;
        other.m_impl = nullptr;
    }
    return *this;
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_impl->handle);
}

void Window::pollEvents() {
    Input::endFrame();
    glfwWaitEventsTimeout(0.016);
}

void Window::swapBuffers() {
    glfwSwapBuffers(m_impl->handle);
}

void Window::run(const std::function<bool()>& onFrame) {
    while (!shouldClose()) {
        pollEvents();
        if (onFrame && !onFrame())
            break;
        swapBuffers();
    }
}

int Window::width() const {
    int w, h;
    glfwGetFramebufferSize(m_impl->handle, &w, &h);
    return w;
}

int Window::height() const {
    int w, h;
    glfwGetFramebufferSize(m_impl->handle, &w, &h);
    return h;
}

void Window::setTitle(const std::string& title) {
    glfwSetWindowTitle(m_impl->handle, title.c_str());
}

} // namespace chisel