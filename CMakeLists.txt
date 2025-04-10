cmake_minimum_required(VERSION 3.13.2)

project(GridForge)

include_directories(ThirdParty/include)
link_directories(ThirdParty/lib)
if(WIN32)
    add_executable(${PROJECT_NAME} test.cpp ThirdParty/src/glad.c "../Assets/Icons/resources.rc")
    #Once making a release add WIN32 so that no console additions are made
    #for now since we debugging i will remove it 
else()
    add_executable(${PROJECT_NAME} test.cpp)
endif()

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} mingw32 SDL2main SDL2 SDL2_image ${OPENGL_gl_LIBRARY})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "../ThirdParty/SDL2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "../ThirdParty/SDL2_image.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)