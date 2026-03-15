cmake_minimum_required(VERSION 4.1)
project(ProjectBrick)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 3.3 REQUIRED)

add_executable(ProjectBrick "lib/gl.c" main.cpp)

target_link_libraries(ProjectBrick glfw GL)