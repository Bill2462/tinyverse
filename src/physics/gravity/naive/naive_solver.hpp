#ifndef NAIVE_GRAVITY_SOLVER_HPP_INCLUDED
#define NAIVE_GRAVITY_SOLVER_HPP_INCLUDED

#include "physics/gravity/gravity_solver.hpp"
#include <functional>

class NaiveGravitySolver : public GravitySolver
{
public:
    NaiveGravitySolver(const Vectors3D& position, const Vector& mass,
    Real G, bool use_softening, Real softening_epsilon = 2);

    Vector3D<Real> compute_net_grawitational_force(std::size_t body_index) const override;
    GravitySolver::Type get_type() const override;
    
private:
    const Vectors3D* position;
    const Vector* mass;
    const Real G;
    const bool use_softening;
    const Real softening_epsilon;
    const std::size_t nbody;
};

#endif
