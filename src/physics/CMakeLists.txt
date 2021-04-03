find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(spdlog REQUIRED)

set(SOURCES
    universe.cpp
    universe_initializers/random/random_initializer.cpp
    universe_initializers/systems/two_body.cpp
    simulation/compute_grawitational_forces.cpp
    simulation/step.cpp
    initialize_universe.cpp
    universe_initializers/initializer_factory.cpp
    ../exceptions/fatal_error.cpp
    ../config/json_loader.cpp
)

include_directories(src)
include_directories("${PROJECT_BINARY_DIR}")
include_directories(${EIGEN3_INCLUDE_DIR})

add_library(tiniverse_physics STATIC ${SOURCES})
target_link_libraries(tiniverse_physics spdlog::spdlog)
target_link_libraries(tiniverse_physics Eigen3::Eigen)
