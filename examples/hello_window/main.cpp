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