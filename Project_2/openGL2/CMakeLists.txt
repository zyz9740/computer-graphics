cmake_minimum_required(VERSION 3.14)
project(openGL2)

set(CMAKE_CXX_STANDARD 11)


set(GLEW_H /usr/local/Cellar/glew/2.1.0/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.3/include/GLFW)
set(GLAD_H /usr/local/include/glad)
set(KH_H /usr/local/include/KHR)
include_directories(${GLEW_H} ${GLFW_H} ${GLAD_H} ${KH_H})

set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

set(SOURCE_FILES "glad.c" "main.cpp")
add_executable(openGL2 ${SOURCE_FILES})

if (APPLE)
    target_link_libraries(openGL2 "-framework OpenGL")
    target_link_libraries(openGL2 "-framework GLUT")
endif()