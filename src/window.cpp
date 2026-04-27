#include "chisel/window.h"

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace chisel {

// IMPL definition

struct Window::Impl {
    GLFWwindow* handle = nullptr;

    Impl(const WindowConfig& cfg) {
        if (!glfwInit())
            throw std::runtime_error("chisel: failed to initialise GLFW");

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE,  cfg.resizable ? GLFW_TRUE : GLFW_FALSE);

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

        glfwSetWindowUserPointer(handle, this);

        glfwSetFramebufferSizeCallback(handle,
            [](GLFWwindow*, int, int) {
                // TODO: Will forward to user callbacks in a later chapter
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

// Window API

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
    glfwWaitEventsTimeout(0.016);
}

void Window::swapBuffers() {
    // TODO!: No-op until a graphics context is attached
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