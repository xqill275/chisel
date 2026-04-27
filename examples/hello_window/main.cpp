#include <chisel/chisel.h>
#include <cstdio>

int main() {
    chisel::WindowConfig cfg;
    cfg.width  = 1280;
    cfg.height = 720;
    cfg.title  = "My Game";

    chisel::Window window(cfg);

    while (!window.shouldClose()) {
        window.pollEvents();

        // Close on Escape
        if (chisel::Input::isKeyPressed(chisel::Key::Escape))
            break;

        // Print mouse position when left button is held
        if (chisel::Input::isMouseButtonDown(chisel::MouseButton::Left)) {
            double x, y;
            chisel::Input::mousePosition(x, y);
            printf("mouse: %.0f, %.0f\n", x, y);
        }

        // Print a message on spacebar press (only fires once per press)
        if (chisel::Input::isKeyPressed(chisel::Key::Space))
            printf("space pressed!\n");

        if (chisel::Input::isKeyDown(chisel::Key::A))
            printf("a \n");

        if (chisel::Input::isMouseButtonPressed(chisel::MouseButton::Middle)) {
            printf("middle button pressed \n");
        }
    }
}