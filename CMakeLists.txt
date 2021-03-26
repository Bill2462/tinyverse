cmake_minimum_required(VERSION 2.9)

project(Tinyverse)

set(EXECUTABLE_NAME tinyverse)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)

configure_file(
  "src/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

set(SOURCES
    src/main.cpp
    src/log/log.cpp
)

include_directories(src)
include_directories("${PROJECT_BINARY_DIR}")

find_package(spdlog REQUIRED)
find_package(SFML 2.0 REQUIRED window graphics)

add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_link_libraries(${EXECUTABLE_NAME} sfml-window sfml-graphics)
target_link_libraries(${EXECUTABLE_NAME} spdlog::spdlog)
