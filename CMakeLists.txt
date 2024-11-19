cmake_minimum_required(VERSION 3.29)
project(PROJECT_2CPP)

set(CMAKE_CXX_STANDARD 20)
# Fetch the nlohmann-json library
include(FetchContent)
FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2  # Specify the version you want to use
)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(PROJECT_2CPP src/main.cpp
        include/Player.hpp
        src/Player.cpp
        src/Tile.cpp
        include/Board.hpp
        include/Case.hpp
        src/Case.cpp
        src/Board.cpp
        include/Game.hpp
        src/Game.cpp
        include/Party.hpp
        src/Party.cpp)
target_include_directories( PROJECT_2CPP PUBLIC include )
target_link_libraries(PROJECT_2CPP PRIVATE nlohmann_json::nlohmann_json)
