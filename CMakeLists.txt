cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)

# Inclure les headers
include_directories(include)

# Ajouter les fichiers source
file(GLOB SOURCES "src/*.cpp" "main.cpp")

# Exécutable
add_executable(snake_game ${SOURCES})

# Lier SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(snake_game sfml-graphics sfml-window sfml-system)
