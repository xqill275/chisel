#pragma once

/**
 * @file chisel.h
 * @brief Include this single header to access all Chisel engine features.
 */

/**
 * @mainpage Chisel Engine
 *
 * A lightweight, code-only 2D game engine written in C++17.
 * No editor, no UI — just a clean library you link against and build with.
 *
 * ## Getting Started
 *
 * Include the single master header:
 * @code
 * #include <chisel/chisel.h>
 * @endcode
 *
 * Create a window and run your game loop:
 * @code
 * int main() {
 *     chisel::WindowConfig cfg;
 *     cfg.width  = 1280;
 *     cfg.height = 720;
 *     cfg.title  = "My Game";
 *
 *     chisel::Window window(cfg);
 *
 *     while (!window.shouldClose()) {
 *         window.pollEvents();
 *
 *         if (chisel::Input::isKeyPressed(chisel::Key::Escape))
 *             break;
 *     }
 * }
 * @endcode
 *
 * ## Modules
 * - **chisel::Window** — native desktop window (v0.1)
 * - **chisel::Input**  — keyboard and mouse input (v0.2)
 */

#include "chisel/window.h"
#include "chisel/input.h"

