cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)

# Ajouter les fichiers d'en-tête
include_directories(include)

# Ajouter tous les fichiers .cpp dans src + main.cpp à la racine
file(GLOB SOURCES "src/*.cpp" "main.cpp")

# Créer l'exécutable
add_executable(snake_game ${SOURCES})

# Lier les bibliothèques SFML nécessaires
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(snake_game sfml-graphics sfml-window sfml-system)

# Copier le dossier assets dans le dossier build/ (important pour les ressources)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

