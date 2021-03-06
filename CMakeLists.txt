cmake_minimum_required(VERSION 2.9)

project(Tinyverse CXX)
set(CMAKE_CXX_STANDARD 17)

set(BUILD_TESTS ON)
set(EXECUTABLE_NAME tinyverse)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)

configure_file(
  "src/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(spdlog REQUIRED)
find_package(Corrade REQUIRED Main)
find_package(Magnum REQUIRED
  GL
  MeshTools
  Primitives
  SceneGraph
  Shaders
  Sdl2Application
)

corrade_add_resource(RESOURCES_CONFIG src/resources.conf)

set(SOURCES
    src/main.cpp
    src/app/app.cpp
    src/app/draw.cpp
    src/app/events.cpp
    src/app/init_sim.cpp
    src/renderer/particle_renderer.cpp
    src/shaders/particle_shader.cpp
    ${RESOURCES_CONFIG}
)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

include_directories(src)
include_directories("${PROJECT_BINARY_DIR}")
include_directories(${EIGEN3_INCLUDE_DIR})

add_subdirectory(src/physics)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_link_libraries(${EXECUTABLE_NAME}
  Corrade::Main
  Magnum::Application
  Magnum::GL
  Magnum::Magnum
  Magnum::MeshTools
  Magnum::Primitives
  Magnum::SceneGraph
  Magnum::Shaders
)

target_link_libraries(${EXECUTABLE_NAME} spdlog::spdlog)
target_link_libraries(${EXECUTABLE_NAME} Eigen3::Eigen)
target_link_libraries(${EXECUTABLE_NAME} tiniverse_physics)
target_link_libraries(${EXECUTABLE_NAME} nlohmann_json::nlohmann_json)

if(${BUILD_TESTS})
  add_subdirectory(tests)
endif()
