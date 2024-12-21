cmake_minimum_required(VERSION 3.13.2)

project(learnSDL2)

add_executable(${PROJECT_NAME} main.cpp)

include(FetchContent)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.30.1
)
FetchContent_MakeAvailable(SDL2)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)