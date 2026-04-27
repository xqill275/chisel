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
 * ## Modules
 * - **chisel::Window**   — native desktop window (v0.1)
 * - **chisel::Input**    — keyboard and mouse input (v0.2)
 * - **chisel::Shader**   — GLSL shader programs (v0.3)
 * - **chisel::Texture**  — 2D texture loading (v0.3)
 * - **chisel::Renderer** — 2D sprite renderer (v0.3)
 * - **chisel::Camera**   — 2D orthographic camera (v0.3)
 */

#include "chisel/window.h"
#include "chisel/input.h"
#include "chisel/shader.h"
#include "chisel/texture.h"
#include "chisel/renderer.h"
#include "chisel/camera.h"

// Coming soon:
// #include "chisel/audio.h"    (v0.5)