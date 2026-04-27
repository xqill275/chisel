# Chisel

A lightweight, code-only 2D game engine written in C++17.

---


## Current Capabilities — v0.1

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

## Dependencies

Chisel requires GLFW to be installed on your system before building.

```bash
# Ubuntu / WSL
sudo apt install libglfw3-dev

# macOS
brew install glfw

# Windows (via vcpkg)
vcpkg install glfw3
```

---

## Building

### Requirements

- CMake 3.22+
- A C++17 compiler (GCC, Clang, or MSVC)
- Git
- GLFW (see above)

### Linux / WSL (Ubuntu)

> **WSL note:** run `echo $DISPLAY` to confirm your display server is working. On Windows 11, WSLg handles this automatically. On Windows 10 you will need VcXsrv or a similar X server and `export DISPLAY=:0`.

```bash
git clone https://github.com/you/chisel.git
cd chisel
cmake -S . -B build
cmake --build build
```

### macOS

```bash
xcode-select --install

git clone https://github.com/you/chisel.git
cd chisel
cmake -S . -B build
cmake --build build
```

### Windows

Open a Developer Command Prompt for Visual Studio, or use MinGW.

```bash
git clone https://github.com/you/chisel.git
cd chisel
cmake -S . -B build
cmake --build build --config Release
```

---

## Usage

Add Chisel to your `CMakeLists.txt`:

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

Examples are built automatically alongside the library. After building, run them from the project root:

```bash
# Linux / macOS / WSL
./build/examples/hello_window/hello_window

# Windows
build\examples\hello_window\Release\hello_window.exe
```

To skip building examples:

```bash
cmake -S . -B build -DCHISEL_BUILD_EXAMPLES=OFF
```

---


