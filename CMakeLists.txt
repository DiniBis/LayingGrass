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

add_executable(PROJECT_2CPP main.cpp)
target_link_libraries(PROJECT_2CPP PRIVATE nlohmann_json::nlohmann_json)
