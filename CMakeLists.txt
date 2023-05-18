cmake_minimum_required(VERSION 3.26)
project(
    pokemon_simulator
    VERSION 1.0
    DESCRIPTION
        "A simple CLI Pokemon simulator that uses Alpha-beta Pruning algorithm for opponent AI."
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 17)

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(pokemon_simulator ${SOURCE_FILES})

# User-defined libraries
add_subdirectory(pokemon)

target_link_libraries(pokemon_simulator
    PRIVATE
        pokemon
)