cmake_minimum_required(VERSION 3.10)

# Project name and version
project(RogueAscent VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Add executable
add_executable(RogueAscent src/main.cpp src/Game.cpp src/Player.cpp "src/Enemy.cpp")

# Link SFML libraries
target_link_libraries(RogueAscent sfml-system sfml-window sfml-graphics)
