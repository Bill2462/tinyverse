// This file contains universe.
// A class that contains all physical bodies and objects.
#ifndef UNIVERSE_HPP_INCLUDED
#define UNIVERSE_HPP_INCLUDED

#include <string>
#include <spdlog/spdlog.h>
#include "physics/common_types.hpp"

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

#endif
