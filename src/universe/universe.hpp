// This file contains universe.
// A class that contains all physical bodies and objects.
#ifndef UNIVERSE_HPP_INCLUDED
#define UNIVERSE_HPP_INCLUDED

#include <utility>
#include <string>
#include <eigen3/Eigen/Dense>
#include <spdlog/spdlog.h>

#include "common_types.hpp"

namespace universe
{
    struct Universe
    {
        Universe():
        nbody(0)
        {}

        Universe(size_t nbody)
        {
            set_size(nbody);
        };
        
        void set_size(size_t nbody)
        {
            this->nbody = nbody;
            position.resize(nbody, 3);
            velocity.resize(nbody, 3);
            mass.resize(nbody, 1);
            
            spdlog::debug(std::string("Universe size set to ") +
            std::to_string(nbody) + std::string("."));
        }

        size_t nbody;
        Vectors3D position;
        Vectors3D velocity;
        Vector mass;
    };

    struct RandomInitializerConfig
    {
       std::pair<Real, Real> position_range;
       std::pair<Real, Real> velocity_range;
       std::pair<Real, Real> mass_range;
    };
    
    void random_universe_initializer(Universe& universe, const RandomInitializerConfig& config);
}

#endif
