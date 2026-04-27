cmake_minimum_required(VERSION 3.22)
project(chisel VERSION 0.1.0 LANGUAGES CXX)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 
# Dependencies 
find_package(glfw3 3.3 REQUIRED)
 
# Library target
add_library(chisel STATIC
    src/window.cpp
)
 
target_include_directories(chisel
    PUBLIC include
)
 
target_link_libraries(chisel
    PRIVATE glfw
)
 
# Examples
option(CHISEL_BUILD_EXAMPLES "Build example programs" ON)
 
if(CHISEL_BUILD_EXAMPLES)
    add_subdirectory(examples/hello_window)
endif()
 
