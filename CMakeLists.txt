cmake_minimum_required(VERSION 3.13.2)

project(learnSDL2)

include_directories(ThirdParty/include)
link_directories(ThirdParty/lib)
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} mingw32 SDL2main SDL2)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "../ThirdParty/SDL2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)