#ifndef UNIVERSE_HPP_INCLUDED
#define UNIVERSE_HPP_INCLUDED

#include <string>
#include <functional>
#include <memory>
#include "physics/common_types.hpp"
#include "universe_initializers/universe_initializers.hpp"

class Universe
{
public:
    struct SimulationConfig
    {
        Real timestep = 0.001;
        Real G = 1;
    };

    Universe(){};
    Universe(size_t n);
    
    // Set amount of bodies that are in the universe.
    void set_size(size_t n);
    size_t get_size() const;

    void set_sim_config(const SimulationConfig& config);
    SimulationConfig get_sim_config() const;

    // Return a reference for accessing positions.
    const Vectors3D& get_positions() const;
    const Vectors3D& get_velocities() const;
    const Vector& get_masses() const;

    void apply_initializer(std::weak_ptr<UniverseInitializer> initializer);
    
    // Advances simulation by one timestep.
    void simulation_step();

    double get_simulaton_time() const;

private:
    // Pass index of the body and get forces acting on the body.
    Vector3D<Real> compute_net_grawitational(std::size_t i);

    SimulationConfig sim_config;
    Real sim_time = 0;
    size_t size = 0;

    Vectors3D position;
    
    Vectors3D velocity;
    Vectors3D acceleration;
    Vector mass;
};

#endif
