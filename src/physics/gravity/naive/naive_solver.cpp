#include "naive_solver.hpp"

NaiveGravitySolver::NaiveGravitySolver(const Vectors3D& position, const Vector& mass,
Real G, bool use_softening, Real softening_epsilon):
    position(&position),
    mass(&mass),
    G(G),
    use_softening(use_softening),
    softening_epsilon(softening_epsilon),
    nbody(position.rows())
{}

Vector3D<Real> NaiveGravitySolver::compute_net_grawitational_force(std::size_t body_index) const
{
    Vector3D<Real> accumulated_force = {0,0,0};

    const Vector3D<Real> r2 = {
            (*position)(body_index, 0),
            (*position)(body_index, 1),
            (*position)(body_index, 2)
    };

    const Real m1 = (*mass)(body_index);

    for(std::size_t k=0; k<nbody; k++)
    {
        if(k == body_index)
            continue;
        
        const Vector3D<Real> distace_vec = {
            r2.x - (*position)(k, 0),
            r2.y - (*position)(k, 1),
            r2.z - (*position)(k, 2),
        };
        
        const Real distance = distace_vec.norm2();

        // Compute term that will be multipled by distance vector.
        Real a;
        if(use_softening)
        {
            Real div = softening_epsilon*softening_epsilon + distance*distance;
            div = sqrt(div*div*div);
            a = (*mass)(k)/div;
        }
        else
            a = (*mass)(k)/(distance*distance*distance);

        // Compute and add new force acting on the body.
        accumulated_force.x += distace_vec.x*a;
        accumulated_force.y += distace_vec.y*a;
        accumulated_force.z += distace_vec.z*a;
    }

    accumulated_force.x *= m1*-1*G;
    accumulated_force.y *= m1*-1*G;
    accumulated_force.z *= m1*-1*G;

    return accumulated_force;
}

GravitySolver::Type NaiveGravitySolver::get_type() const
{
    return GravitySolver::Type::NAIVE;
}
