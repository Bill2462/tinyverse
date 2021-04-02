#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED

#include <utility>
#include <string>
#include "physics/common_types.hpp"
#include "physics/vector_3D.hpp"

struct UniverseConfig
{
    enum class Initializer
    {
        RANDOM,
        TWO_BODY,
    };

    Initializer initializer_type = Initializer::RANDOM;
    std::size_t universe_size = 1000;
    bool default_config = true;
};

struct SimulationConfig
{
    Real timestep = 0.001;
    Real G = 1;
    bool use_softening = true;
    Real epsilon = 2; // Coefficient used for softening of the gravity. Use in colisionless simulations.
    bool default_config = true;
};

struct RandomInitializerConfig
{
    std::pair<Real, Real> position_range = {-10, 10};
    std::pair<Real, Real> mass_range = {0.01, 50};
    std::pair<Real, Real> velocity_range;

    bool zero_vel = true;
    bool default_config = true;
};

struct TwoBodyInitializerConfig
{
    Real body1_mass = 1000;
    Real body2_mass = 0.1;
    Vector3D<Real> body2_velocity = {0, 0, 1};
    Vector3D<Real> body2_position = {0, 32, 0};
    bool default_config = true;
};

#endif
