// The goal of this test is to demonstrate the stability of the integrator.
// We will do this by simulating a two body system and plotting the trajectory over time
// to see if the amount of energy in the system changes.

#define _USE_MATH_DEFINES
#include "physics/universe.hpp"
#include "../matplotlib_cpp/matplotlibcpp.h"
#include <cmath>
#include <vector>

namespace plt = matplotlibcpp;

constexpr std::size_t NSTEPS = 100000;
int main()
{
    // Build universe and initialize a two body system.
    Universe universe;
    const size_t n_body = 2;
    universe.set_size(n_body);
    
    SimulationConfig sim_config;
    sim_config.use_softening = false;
    universe.set_sim_config(sim_config);

    auto initializer = std::make_shared<TwoBodyInitializer>();
    TwoBodyInitializerConfig universe_initializer_config;
    universe_initializer_config.body1_mass = 1000;
    universe_initializer_config.body2_mass = 1;
    universe_initializer_config.body2_position = {0, 0, 1};
    universe_initializer_config.body2_velocity = {0, 32, 0};
    initializer->set_config(universe_initializer_config);
    universe.apply_initializer(initializer);

    std::vector<Real> x, y, z, energy;
    x.resize(NSTEPS);
    y.resize(NSTEPS);
    z.resize(NSTEPS);
    energy.resize(NSTEPS);

    for(std::size_t i=0; i<NSTEPS; i++)
    {
        universe.simulation_step();
        const Vector3D<Real> pos1 = 
        {
            universe.get_positions()(0, 0),
            universe.get_positions()(0, 1),
            universe.get_positions()(0, 2)
        };

        const Vector3D<Real> pos2 = 
        {
            universe.get_positions()(1, 0),
            universe.get_positions()(1, 1),
            universe.get_positions()(1, 2)
        };

        x[i] = pos2.x;
        y[i] = pos2.y;
        z[i] = pos2.z;

        // Compute total kinetic energy of the system.
        const Vector3D<Real> vel1 = 
        {
            universe.get_velocities()(0, 0),
            universe.get_velocities()(0, 1),
            universe.get_velocities()(0, 2),
        };
        const Vector3D<Real> vel2 = 
        {
            universe.get_velocities()(1, 0),
            universe.get_velocities()(1, 1),
            universe.get_velocities()(1, 2),
        };

        const Real mass1 = universe.get_masses()(0);
        const Real mass2 = universe.get_masses()(1);
        const Real spd1 = vel1.norm2();
        const Real spd2 = vel2.norm2();

        energy[i] = (spd1*spd1)*mass1*static_cast<Real>(0.5);
        energy[i] += (spd2*spd2)*mass2*static_cast<Real>(0.5);

        // Compute total potential energy
        const Vector3D<Real> distance_vec = 
        {
            pos1.x - pos2.x,
            pos1.y - pos2.y,
            pos1.z - pos2.z
        };

        const Real G = universe.get_sim_config().G;

        energy[i] += -G*((mass1*mass2)/distance_vec.norm2());
    }

    plt::plot3(x, y, z);
    plt::show();
    plt::plot(energy);
    plt::show();

    return 0;
}
