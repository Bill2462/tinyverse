#include "disc.hpp"
#include <cmath>
#include <chrono>

DiscInitializer::DiscInitializer()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    gen.seed(seed);
}

DiscInitializer::DiscInitializer(std::weak_ptr<ConfigurationLoader> config_loader)
{
    DiscInitializer();
    init(config_loader);
}

void DiscInitializer::init(std::weak_ptr<ConfigurationLoader> config_loader)
{
    if(auto ptr = config_loader.lock())
    {
        radius_range = ptr->get_pair("initializer_config", "radius_range");
        mass_range = ptr->get_pair("initializer_config", "mass_range");
        center_mass =  ptr->get_real("initializer_config", "center_body_mass");
        G = ptr->get_real("simulation_config", "G");
    }
    else
        throw(DiscInitializerInitializerException("Invalid config loader!"));
}

void DiscInitializer::set_position(Vectors3D& pos) const
{
    generate_bodies(pos.rows());

    pos = positions;
}

void DiscInitializer::set_velocity(Vectors3D& vel) const
{
    generate_bodies(vel.rows());
    vel = velocities;
}

void DiscInitializer::set_mass(Vector& mass) const
{
    generate_bodies(mass.rows());
    mass = masses;
}

void DiscInitializer::generate_bodies(std::size_t size) const
{
    if(bodies_generated)
        return;

    positions.resize(size, 3);
    velocities.resize(size, 3);
    masses.resize(size, 1);

    // Generate center body
    positions(0, 0) = 0;
    positions(0, 1) = 0;
    positions(0, 2) = 0;
    
    velocities(0, 0) = 0;
    velocities(0, 1) = 0;
    velocities(0, 2) = 0;

    masses(0) = center_mass;

    // Generate random masses and random positions wthin the ring.
    std::uniform_real_distribution<Real> radius_dist(radius_range.first, radius_range.second);
    std::uniform_real_distribution<Real> angle_dist(0, 2*M_PI);
    std::uniform_real_distribution<Real> mass_dist(mass_range.first, mass_range.second);

    for(std::size_t i=1; i<size; i++)
    {
        // Sample from the radius and circle, angle and mass.
        const Real radius = radius_dist(gen);
        const Real angle = angle_dist(gen);
        masses(i) = mass_dist(gen);

        // Compute position.
        positions(i, 0) = radius*std::cos(angle);
        positions(i, 1) = radius*std::sin(angle);
        positions(i, 2) = 0;

        // Compute orbital velocity for this point.
        // Note: Position is also a distance from the center since center is at (0,0,0).
        const Real v = std::sqrt((G*center_mass) / radius);

        // Calculate position
        velocities(i, 0) = -std::sin(angle)*v;
        velocities(i, 1) = std::cos(angle)*v;
        velocities(i, 2) = 0;
    }

    bodies_generated = true;
}

std::string DiscInitializer::get_name() const
{
    return "Disc Initializer";
}
