// Implements velocity verlet method.
#include "physics/universe.hpp"
#include "physics/vector_3D.hpp"

void Universe::update_integrator()
{
    for(std::size_t i=0; i<get_size(); i++)
    {
        // Acceleration
        const Vector3D<Real> acceleration = 
        {
            forces(i, 0)/mass(i),
            forces(i, 1)/mass(i),
            forces(i, 2)/mass(i)
        };
        
        // Advance velocity by half step.
        velocity(i, 0) += acceleration.x*sim_config.timestep*static_cast<Real>(0.5);
        velocity(i, 1) += acceleration.y*sim_config.timestep*static_cast<Real>(0.5);
        velocity(i, 2) += acceleration.z*sim_config.timestep*static_cast<Real>(0.5);

        // Update position.
        position(i, 0) += velocity(i, 0)*sim_config.timestep;
        position(i, 1) += velocity(i, 1)*sim_config.timestep;
        position(i, 2) += velocity(i, 2)*sim_config.timestep;

        // Advance velocity by another half step.
        velocity(i, 0) += acceleration.x*sim_config.timestep*static_cast<Real>(0.5);
        velocity(i, 1) += acceleration.y*sim_config.timestep*static_cast<Real>(0.5);
        velocity(i, 2) += acceleration.z*sim_config.timestep*static_cast<Real>(0.5);
    }
}
