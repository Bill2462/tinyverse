#ifndef UNIVERSE_BASE_INITIALIZER_HPP_INCLUDED
#define UNIVERSE_BASE_INITIALIZER_HPP_INCLUDED

#include <memory>
#include <string>
#include "physics/common_types.hpp"

struct UniverseInitializer
{
    virtual void set_position(Vectors3D& pos, std::size_t body_count) const = 0;
    virtual void set_velocity(Vectors3D& vel, std::size_t body_count) const = 0;
    virtual void set_mass(Vector& mass, std::size_t body_count) const = 0;
    virtual std::string get_name() const = 0;

    virtual ~UniverseInitializer() = default;
};

#endif
