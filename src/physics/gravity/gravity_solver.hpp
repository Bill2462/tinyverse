#ifndef GRAVITY_SOLVER_HPP_INCLUDED
#define GRAVITY_SOLVER_HPP_INCLUDED

#include "physics/common_types.hpp"
#include "physics/vector_3D.hpp"

struct GravitySolver
{
    virtual Vector3D<Real> compute_net_grawitational_force(std::size_t body_index) const = 0;

    enum class Type
    {
        NAIVE
    };

    virtual Type get_type() const = 0;
};

#endif
