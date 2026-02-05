cmake_minimum_required(VERSION 3.20)

project(physics_sim
    VERSION 0.1.0
    LANGUAGES CXX
)

# -----------------------------
# Global configuration
# -----------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------
# Header-only simulation library
# -----------------------------
add_library(simulation INTERFACE)

target_include_directories(simulation
    INTERFACE
        ${CMAKE_SOURCE_DIR}/src
)

# -----------------------------
# Catch2 (unit tests)
# -----------------------------
include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.2
)

FetchContent_MakeAvailable(Catch2)

# -----------------------------
# Tests executable
# -----------------------------
add_executable(tests
    tests/VectorTests.cpp
    tests/PhysicsTests.cpp
)

target_link_libraries(tests
    PRIVATE
        simulation
        Catch2::Catch2WithMain
)

if (MSVC)
    target_compile_options(tests PRIVATE /W4)
else()
    target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
add_test(NAME physics_tests COMMAND tests)

# -----------------------------
# SFML 3 (Visualization)
# -----------------------------
if(NOT DEFINED SFML_DIR)
    message(FATAL_ERROR "SFML_DIR not set; set it to C:/libs/SFML-3.0.0/lib/cmake/SFML")
endif()

find_package(SFML CONFIG REQUIRED COMPONENTS Graphics Window System)

# -----------------------------
# Projectile visualization demo
# -----------------------------
add_executable(projectile_demo
    apps/ProjectileDemo.cpp
    src/viz/SfmlRenderer.cpp
)

target_include_directories(projectile_demo
    PRIVATE
        src
        src/viz
)

target_link_libraries(projectile_demo
    PRIVATE
        simulation
        SFML::Graphics
        SFML::Window
        SFML::System
)

if (MSVC)
    target_compile_options(projectile_demo PRIVATE /W4)
else()
    target_compile_options(projectile_demo PRIVATE -Wall -Wextra -Wpedantic)
endif()
