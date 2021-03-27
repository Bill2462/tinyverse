// This file contains universe.
// A class that contains all physical bodies and objects.
#ifndef UNIVERSE_HPP_INCLUDED
#define UNIVERSE_HPP_INCLUDED

#include <eigen3/Eigen/Dense>
#include <memory>
#include <utility>
#include "common_types.hpp"

namespace universe
{
    struct Universe
    {
        Universe(size_t nbody)
        {
            this->nbody = nbody;
            position.resize(nbody, 3);
            velocity.resize(nbody, 3);
            mass.resize(nbody, 1);
        };

        size_t nbody;
        Vectors3D position;
        Vectors3D velocity;
        Vector mass;
    };

    struct RandomInitializerConfig
    {
       std::pair<double, double> position_range;
       std::pair<double, double> velocity_range;
       std::pair<double, double> mass_range;
    };
    
    void random_universe_initializer(Universe& universe, const RandomInitializerConfig& config);
}

#endif
