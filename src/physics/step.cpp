#include "physics/universe.hpp"
#include "physics/vector_3D.hpp"
#include "physics/gravity/barnes_hut/barnes_hut.hpp"

void Universe::simulation_step()
{
    if(gravity_solver->get_type() == GravitySolver::Type::BARNES_HUT)
        static_cast<BarnesHutGravitySolver*>(gravity_solver.get())->rebuild_tree();


    for(std::size_t i=0; i<get_size(); i++)
    {
        position(i, 0) += velocity(i, 0)*timestep + acceleration(i, 0)*timestep*timestep*static_cast<Real>(0.5);
        position(i, 1) += velocity(i, 1)*timestep + acceleration(i, 1)*timestep*timestep*static_cast<Real>(0.5);
        position(i, 2) += velocity(i, 2)*timestep + acceleration(i, 2)*timestep*timestep*static_cast<Real>(0.5);
    }
    
    for(std::size_t i=0; i<get_size(); i++)
    {
        velocity(i, 0) += acceleration(i, 0)*timestep*static_cast<Real>(0.5);
        velocity(i, 1) += acceleration(i, 1)*timestep*static_cast<Real>(0.5);
        velocity(i, 2) += acceleration(i, 2)*timestep*static_cast<Real>(0.5);
    }

    for(std::size_t i=0; i<get_size(); i++)
    {
        const Vector3D<Real> forces = gravity_solver->compute_net_grawitational_force(i);
        acceleration(i, 0) = forces.x/mass(i);
        acceleration(i, 1) = forces.y/mass(i);
        acceleration(i, 2) = forces.z/mass(i);
    }

    for(std::size_t i=0; i<get_size(); i++)
    {
        velocity(i, 0) += acceleration(i, 0)*timestep*static_cast<Real>(0.5);
        velocity(i, 1) += acceleration(i, 1)*timestep*static_cast<Real>(0.5);
        velocity(i, 2) += acceleration(i, 2)*timestep*static_cast<Real>(0.5);
    }

    sim_time += timestep;
}
