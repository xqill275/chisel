cmake_minimum_required(VERSION 3.22)
project(chisel VERSION 0.3.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies 
find_package(glfw3  3.3 REQUIRED)
find_package(OpenGL     REQUIRED)

# glad (bundled)
add_library(glad STATIC
    third_party/src/glad.c
)

target_include_directories(glad
    PUBLIC third_party/include
)

# Library target 
add_library(chisel STATIC
    src/window.cpp
    src/input.cpp
    src/shader.cpp
    src/texture.cpp
    src/renderer.cpp
    src/camera.cpp
)

target_include_directories(chisel
    PUBLIC  include
    PRIVATE third_party/include
)

target_link_libraries(chisel
    PUBLIC  glad
    PRIVATE glfw
            OpenGL::GL
)

# Examples 
option(CHISEL_BUILD_EXAMPLES "Build example programs" ON)

if(CHISEL_BUILD_EXAMPLES)
    add_subdirectory(examples/hello_window)
    add_subdirectory(examples/game)
endif()