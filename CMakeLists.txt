cmake_minimum_required(VERSION 2.9)

project(Tinyverse)

set(EXECUTABLE_NAME tinyverse)

set(SOURCES
    src/main.cpp
)

include_directories(src)

find_package(SFML 2.0 REQUIRED window graphics)

add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_link_libraries(${EXECUTABLE_NAME} sfml-window sfml-graphics)
