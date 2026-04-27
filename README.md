# Chisel

A lightweight, code-only 2D game engine written in C++17. No editor, no UI — just a clean library you link against and build with. Chisel is the spiritual successor to TextSmith, built for 2D games.

---

## Philosophy

Most engines come with an editor, a launcher, a project wizard, and a hundred settings you never touch. Chisel doesn't. You write code, you link the library, you ship a game. That's it.

---

## Current Capabilities

- **Window management** — create and configure a native desktop window with a single call
- **Cross-platform** — builds on Linux, macOS, and Windows from the same codebase
- **Clean API** — one header to include, one namespace to work in

---

## Roadmap

### v0.2 — Input
- Keyboard state queries (`isKeyDown`, `isKeyPressed`)
- Mouse position and button state
- Event callbacks for key/mouse events

### v0.3 — Renderer
- OpenGL context attached to the window
- 2D sprite rendering
- Basic camera with pan and zoom

### v0.4 — Asset Loading
- Texture loading from PNG/JPG via stb_image
- Spritesheet and atlas support
- Basic asset manager with caching

### v0.5 — Audio
- Sound effect playback
- Background music with looping
- Volume control per channel

### v0.6 — 2D Physics
- AABB collision detection
- Simple rigid body movement
- Tilemap collision support

### v1.0 — First stable release
- Scene management
- Entity component system
- Serialisation (save/load game state)
- Full documentation

---

## Building

Chisel uses CMake and fetches its own dependencies — minimal setup required.

### Requirements

- CMake 3.22+
- A C++17 compiler (GCC, Clang, or MSVC)
- Git

### Linux / WSL (Ubuntu)

Install the system libraries GLFW needs:

```bash
sudo apt install libx11-dev libxrandr-dev libxinerama-dev \
                 libxcursor-dev libxi-dev libgl1-mesa-dev
```

> **WSL note:** run `echo $DISPLAY` to confirm your display server is working. On Windows 11, WSLg handles this automatically. On Windows 10 you will need VcXsrv or a similar X server and `export DISPLAY=:0`.

```bash
git clone https://github.com/you/chisel.git
cd chisel
mkdir build && cd build
cmake ..
cmake --build .
```

### macOS

```bash
xcode-select --install

git clone https://github.com/you/chisel.git
cd chisel
mkdir build && cd build
cmake ..
cmake --build .
```

### Windows

Open a Developer Command Prompt for Visual Studio, or use MinGW. No extra dependencies needed.

```bash
git clone https://github.com/you/chisel.git
cd chisel
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

---

## Usage

Add Chisel to your CMakeLists.txt:

```cmake
add_executable(my_game main.cpp)
target_link_libraries(my_game PRIVATE chisel)
```

Then in your code — one include, and you have everything:

```cpp
#include <chisel/chisel.h>

int main() {
    chisel::WindowConfig cfg;
    cfg.width  = 1280;
    cfg.height = 720;
    cfg.title  = "My Game";

    chisel::Window window(cfg);

    while (!window.shouldClose()) {
        window.pollEvents();
        // your game logic here
    }
}
```

---

## Examples

Examples are built automatically alongside the library. After building, run them from the build directory:

```bash
# Linux / macOS / WSL
./examples/hello_window/hello_window

# Windows
examples\hello_window\Release\hello_window.exe
```

To skip building examples:

```bash
cmake .. -DCHISEL_BUILD_EXAMPLES=OFF
```

---

## Project Structure

```
chisel/
├── include/
│   └── chisel/
│       ├── chisel.h      # the only header you need to include
│       └── window.h
├── src/
│   └── window.cpp
├── examples/
│   └── hello_window/
└── CMakeLists.txt
```
