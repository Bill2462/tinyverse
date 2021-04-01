#include "universe.hpp"
#include <spdlog/spdlog.h>

Universe::Universe(size_t n)
{
    set_size(n);
}

void Universe::set_size(size_t n)
{
    size = n;
    position.resize(size, 3);
    velocity.resize(size, 3);
    acceleration.resize(size, 3);
    mass.resize(size, 1);

    spdlog::debug(std::string("Universe size set to ") +
    std::to_string(n) + std::string("."));
}

size_t Universe::get_size() const
{
    return size;
}

const Vectors3D& Universe::get_positions() const
{
    return position;
}

const Vectors3D& Universe::get_velocities() const
{
    return velocity;
}

const Vector& Universe::get_masses() const
{
    return mass;
}

void Universe::apply_initializer(std::weak_ptr<UniverseInitializer> initializer)
{
    if(auto ptr = initializer.lock())
    {
        ptr->set_position(position, get_size());
        ptr->set_velocity(velocity, get_size());
        ptr->set_mass(mass, get_size());
        spdlog::info(std::string("Universe initialized succesfully using: ") +
        ptr->get_name());
    }
    else
    {
        spdlog::error("Invalid initializer passed to the universe!");
    }
    
    // Initialize accelerations.
    for(std::size_t i=0; i<get_size(); i++)
    {
        Vector3D<Real> forces = compute_net_grawitational(i);
        acceleration(i, 0) = forces.x/mass(i);
        acceleration(i, 1) = forces.y/mass(i);
        acceleration(i, 2) = forces.z/mass(i);
    }
}

void Universe::set_sim_config(const Universe::SimulationConfig& config)
{
    sim_config = config;
}

Universe::SimulationConfig Universe::get_sim_config() const
{
    return sim_config;
}

double Universe::get_simulaton_time() const
{
    return sim_time;
}
