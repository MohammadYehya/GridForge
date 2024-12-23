cmake_minimum_required(VERSION 3.13.2)

project(GridForge)

include_directories(ThirdParty/include)
link_directories(ThirdParty/lib)
# add_executable(${PROJECT_NAME} main.cpp)
if(WIN32)
    add_executable(${PROJECT_NAME} main.cpp "../Assets/Icons/resources.rc")
    #Once making a release add WIN32 so that no console additions are made
    #for now since we debugging i will remove it 
else()
    add_executable(${PROJECT_NAME} main.cpp)
endif()

target_link_libraries(${PROJECT_NAME} mingw32 SDL2main SDL2 SDL2_image)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "../ThirdParty/SDL2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "../ThirdParty/SDL2_image.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)