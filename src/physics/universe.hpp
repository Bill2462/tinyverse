#ifndef UNIVERSE_HPP_INCLUDED
#define UNIVERSE_HPP_INCLUDED

#include <memory>
#include "physics/common_types.hpp"
#include "physics/vector_3D.hpp"
#include "config/config_loader.hpp"
#include "exceptions/fatal_error.hpp"

class Universe
{
public:
    Universe(){};

    size_t get_size() const;

    // Initialize simulation according to the provided configuration.
    void init(std::weak_ptr<ConfigurationLoader> config_loader);

    // Return a reference for accessing positions.
    const Vectors3D& get_positions() const;
    const Vectors3D& get_velocities() const;
    const Vector& get_masses() const;
    
    // Advances simulation by one timestep.
    void simulation_step();

    Real get_simulaton_time() const;

private:
    void set_size(size_t n);

    // Pass index of the body and get forces acting on the body.
    Vector3D<Real> compute_net_grawitational(std::size_t i);
    Real sim_time = 0;
    size_t size = 0;

    Vectors3D position;
    Vectors3D velocity;
    Vectors3D acceleration;
    Vector mass;

    Real timestep = 0.001;
    Real G = 1;
    bool use_softening = true;
    Real softening_epsilon = 2;
};

struct UniverseException : public FatalError
{
    UniverseException(const std::string& message):
    FatalError(message)
    {}
};

#endif
