#include <chisel/chisel.h>



static constexpr int   WINDOW_W     = 1280;
static constexpr int   WINDOW_H     = 720;
static constexpr int   TILE_SIZE    = 64;
static constexpr int   MAP_W        = 20;   // tiles
static constexpr int   MAP_H        = 15;
static constexpr float PLAYER_SPEED = 3.0f;
static constexpr float PLAYER_SIZE  = 64.0f;

int main() {
    // Window / renderer / camera
    chisel::WindowConfig cfg;
    cfg.width  = WINDOW_W;
    cfg.height = WINDOW_H;
    cfg.title  = "Top-Down Demo";

    chisel::Window   window(cfg);
    chisel::Renderer renderer(WINDOW_W, WINDOW_H);
    chisel::Camera   camera(WINDOW_W, WINDOW_H);

    // Assets
    chisel::Texture playerTex("examples/game/sprites/player.png");
    chisel::Texture floorTex ("examples/game/sprites/floor.png");

    // Player state
    float playerX = (MAP_W * TILE_SIZE) * 0.5f;
    float playerY = (MAP_H * TILE_SIZE) * 0.5f;

    //  Game loop 
    while (!window.shouldClose()) {
        window.pollEvents();

        if (chisel::Input::isKeyPressed(chisel::Key::Escape))
            break;

        // Input
        float dx = 0.0f, dy = 0.0f;
        if (chisel::Input::isKeyDown(chisel::Key::W)) dy -= PLAYER_SPEED;
        if (chisel::Input::isKeyDown(chisel::Key::S)) dy += PLAYER_SPEED;
        if (chisel::Input::isKeyDown(chisel::Key::A)) dx -= PLAYER_SPEED;
        if (chisel::Input::isKeyDown(chisel::Key::D)) dx += PLAYER_SPEED;

        // Normalise diagonal movement
        if (dx != 0.0f && dy != 0.0f) {
            dx *= 0.7071f;
            dy *= 0.7071f;
        }

        // Movement + world bounds 
        playerX += dx;
        playerY += dy;

        float maxX = MAP_W * TILE_SIZE - PLAYER_SIZE;
        float maxY = MAP_H * TILE_SIZE - PLAYER_SIZE;
        if (playerX < 0.0f)  playerX = 0.0f;
        if (playerY < 0.0f)  playerY = 0.0f;
        if (playerX > maxX)  playerX = maxX;
        if (playerY > maxY)  playerY = maxY;

        // Camera follows player
        camera.setPosition(playerX + PLAYER_SIZE * 0.5f,
                           playerY + PLAYER_SIZE * 0.5f);

        // Render 
        renderer.begin(camera, 0.08f, 0.08f, 0.08f);

        // Draw floor tiles
        for (int ty = 0; ty < MAP_H; ++ty) {
            for (int tx = 0; tx < MAP_W; ++tx) {
                renderer.drawSprite(floorTex,
                    (float)(tx * TILE_SIZE),
                    (float)(ty * TILE_SIZE),
                    (float)TILE_SIZE, (float)TILE_SIZE);
            }
        }

        // Draw player
        renderer.drawSprite(playerTex, playerX, playerY,
                            PLAYER_SIZE, PLAYER_SIZE);

        renderer.end();
        window.swapBuffers();
    }

    return 0;
}