cmake_minimum_required(VERSION 3.22)
project(sfml_doodle_jump)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(sfml_doodle_jump src/Application.cpp headers/Menu.hpp src/Menu.cpp headers/BasePlatform.hpp headers/Doodle.hpp headers/Obstacle.hpp headers/MovablePlatform.hpp headers/StaticPlatform.hpp src/Doodle.cpp headers/Platforms.hpp)

target_link_libraries(sfml_doodle_jump sfml-graphics sfml-audio -lglut -lGLU -lGL)