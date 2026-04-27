#include <chisel/chisel.h>

int main() {
    chisel::WindowConfig cfg;
    cfg.width  = 1280;
    cfg.height = 720;
    cfg.title  = "My Game";

    chisel::Window   window(cfg);
    chisel::Renderer renderer(cfg.width, cfg.height);
    chisel::Camera   camera(cfg.width, cfg.height);
    chisel::Texture  texture("assets/sprites/player.png");

    float x = 100.0f, y = 100.0f;

    while (!window.shouldClose()) {
        window.pollEvents();

        if (chisel::Input::isKeyPressed(chisel::Key::Escape))
            break;

        // Move sprite with WASD
        if (chisel::Input::isKeyDown(chisel::Key::D)) x += 2.0f;
        if (chisel::Input::isKeyDown(chisel::Key::A)) x -= 2.0f;
        if (chisel::Input::isKeyDown(chisel::Key::S)) y += 2.0f;
        if (chisel::Input::isKeyDown(chisel::Key::W)) y -= 2.0f;

        // Pan camera with arrow keys
        if (chisel::Input::isKeyDown(chisel::Key::Right)) camera.move( 2.0f,  0.0f);
        if (chisel::Input::isKeyDown(chisel::Key::Left))  camera.move(-2.0f,  0.0f);
        if (chisel::Input::isKeyDown(chisel::Key::Down))  camera.move( 0.0f,  2.0f);
        if (chisel::Input::isKeyDown(chisel::Key::Up))    camera.move( 0.0f, -2.0f);

        // Zoom with Q and E
        if (chisel::Input::isKeyDown(chisel::Key::E)) camera.zoomBy(1.01f);
        if (chisel::Input::isKeyDown(chisel::Key::Q)) camera.zoomBy(0.99f);

        renderer.begin(camera);
        renderer.drawSprite(texture, x, y, 64.0f, 64.0f);
        renderer.end();

        window.swapBuffers();
    }
}