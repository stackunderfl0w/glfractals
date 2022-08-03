cmake_minimum_required(VERSION 3.15)
project(glfractals)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(glfractals main.cpp
        shaderloader.cpp shaderloader.h shader.h
        textureloader.cpp textureloader.h
        imgui/imgui_impl_sdl.cpp
        imgui/imgui_impl_opengl3.cpp
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_widgets.cpp)
#target_link_libraries(glfractals OpenGL32 GLew32 sdl2main sdl2)
target_link_libraries(glfractals GLEW OpenGL SDL2main SDL2)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/pal.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
