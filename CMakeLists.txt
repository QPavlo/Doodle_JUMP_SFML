cmake_minimum_required(VERSION 3.22)
project(sfml_doodle_jump)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(sfml_doodle_jump
        src/Application.cpp src/Menu.cpp
        src/Doodle.cpp
        src/StaticPlatform.cpp
        src/MovablePlatform.cpp
        headers/StaticPlatforms.hpp
        headers/Platforms.hpp
        headers/MovablePlatforms.hpp
        src/Platforms.cpp
        src/MovablePlatforms.cpp src/StaticPlatforms.cpp src/Obstacle.cpp)

target_link_libraries(sfml_doodle_jump sfml-graphics sfml-audio -lglut -lGLU -lGL)