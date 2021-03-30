#include "physics/universe.hpp"
#include "physics/vector_3D.hpp"

void Universe::update_gravity()
{
    for(std::size_t i=0; i<get_size(); i++)
    {
        Vector3D<Real> accumulated_force = {0,0,0};
        const Vector3D<Real> r1 = {
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
                r1.x - position(k, 0),
                r1.y - position(k, 1),
                r1.z - position(k, 2),
            };
            const Real distance = distace_vec.norm2();

            // Compute term that will be multipled by distance vector.
            const Real a = (-1*sim_config.G*m1*mass(k))/
            (distance*distance*distance);

            // Compute and add new force acting on the body.
            accumulated_force.x += distace_vec.x*a;
            accumulated_force.y += distace_vec.y*a;
            accumulated_force.z += distace_vec.z*a;
        }

        // Save computecomputedd force.
        forces(i, 0) = accumulated_force.x;
        forces(i, 1) = accumulated_force.y;
        forces(i, 2) = accumulated_force.z;
    }
}
