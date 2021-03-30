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
    mass.resize(size, 1);
    spdlog::debug(std::string("Universe size set to ") +
    std::to_string(n) + std::string("."));
}

size_t Universe::get_size() const
{
    return size;
}

const Vectors3D& Universe::positions() const
{
    return position;
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
}
