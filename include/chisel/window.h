#pragma once

#include <string>
#include <functional>

namespace chisel {

struct WindowConfig {
    int         width     = 1280;
    int         height    = 720;
    std::string title     = "Chisel Window";
    bool        resizable = true;
    bool        vsync     = true;
};

class Window {
public:
    explicit Window(const WindowConfig& config = {});
    ~Window();

    Window(const Window&)            = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&)                 noexcept;
    Window& operator=(Window&&)      noexcept;

    bool shouldClose() const;
    void pollEvents();
    void swapBuffers();

    // Runs the main loop; return false from onFrame to quit early
    void run(const std::function<bool()>& onFrame = nullptr);

    int  width()  const;
    int  height() const;
    void setTitle(const std::string& title);

private:
    struct Impl;
    Impl* m_impl = nullptr;
};

} // namespace chisel