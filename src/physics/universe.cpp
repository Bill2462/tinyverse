#include "universe.hpp"
#include <spdlog/spdlog.h>

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

Real Universe::get_simulaton_time() const
{
    return sim_time;
}
