#include "random_initializer.hpp"
#include <chrono>

RandomInitializer::RandomInitializer()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    gen.seed(seed);
}

RandomInitializer::RandomInitializer(std::weak_ptr<ConfigurationLoader> config_loader)
{
    RandomInitializer();
    init(config_loader);
}

void RandomInitializer::init(std::weak_ptr<ConfigurationLoader> config_loader)
{
    if(auto ptr = config_loader.lock())
    {
        position_range = ptr->get_pair("initializer_config", "position_range");
        mass_range = ptr->get_pair("initializer_config", "mass_range");

        if(ptr->has_parameter("initializer_config", "zero_velocity"))
            zero_velocity = ptr->get_bool("initializer_config", "zero_velocity");
        else
            zero_velocity = false;

        if(!zero_velocity)
            velocity_range = ptr->get_pair("initializer_config", "velocity_range");
    }
    else
        throw(RandomInitializerException("Invalid config loader!"));
}

inline std::uniform_real_distribution<Real> 
_uniform_dist_from_pair(const std::pair<Real, Real>& range)
{
    return std::uniform_real_distribution<Real> (range.first,
    range.second);
}

void RandomInitializer::set_position(Vectors3D& pos) const
{
    auto dist = _uniform_dist_from_pair(position_range);
    for(size_t i=0; i<pos.rows(); i++)
    {
        for(uint8_t k=0; k<3; k++)
           pos(i, k) = dist(gen);
    }
}

void RandomInitializer::set_velocity(Vectors3D& vel) const
{
    auto dist = _uniform_dist_from_pair(velocity_range);
    for(size_t i=0; i<vel.rows(); i++)
    {
        for(uint8_t k=0; k<3; k++)
        {
            if(zero_velocity)
                vel(i, k) = 0;
            else
                vel(i, k) = dist(gen);
        }
    }
}

void RandomInitializer::set_mass(Vector& mass) const
{
    auto dist = _uniform_dist_from_pair(mass_range);
    for(size_t i=0; i<mass.rows(); i++)
    {
        mass(i) = dist(gen);
    }
}

std::string RandomInitializer::get_name() const
{
    return "Random Initializer";
}