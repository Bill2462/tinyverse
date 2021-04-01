#include "physics/universe.hpp"

Vector3D<Real> Universe::compute_net_grawitational(std::size_t i)
{
    Vector3D<Real> accumulated_force = {0,0,0};

    const Vector3D<Real> r2 = {
            position(i, 0),
            position(i, 1),
            position(i, 2)
    };

    const Real m1 = mass(i);

    for(std::size_t k=0; k<get_size(); k++)
    {
        if(k == i)
            continue;
        
        const Vector3D<Real> distace_vec = {
            r2.x - position(k, 0),
            r2.y - position(k, 1),
            r2.z - position(k, 2),
        };
        
        const Real distance = distace_vec.norm2();

        // Compute term that will be multipled by distance vector.
        const Real a = (mass(k))/
        (distance*distance*distance);

        // Compute and add new force acting on the body.
        accumulated_force.x += distace_vec.x*a;
        accumulated_force.y += distace_vec.y*a;
        accumulated_force.z += distace_vec.z*a;
    }

    accumulated_force.x *= m1*-1*sim_config.G;
    accumulated_force.y *= m1*-1*sim_config.G;
    accumulated_force.z *= m1*-1*sim_config.G;

    return accumulated_force;
}
