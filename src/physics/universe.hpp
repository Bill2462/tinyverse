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

    // Return a reference for accessing positions.
    const Vectors3D& get_positions() const;

    void apply_initializer(std::weak_ptr<UniverseInitializer> initializer);
    
    // Advances simulation by one timestep.
    void advance_simulation();

    double get_simulaton_time() const;

private:
    // Function for updating gravitional forces between bodies.
    void update_gravity();

    // Advance to the next step on the leapfrog integrator.
    void update_integrator();

    SimulationConfig sim_config;
    double sim_time = 0; // Current timestamp of the simulation.
    size_t size = 0;
    Vectors3D position;
    Vectors3D velocity;
    Vectors3D forces;
    Vector mass;
};

#endif
