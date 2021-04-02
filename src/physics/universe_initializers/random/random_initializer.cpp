#include "random_initializer.hpp"
#include <chrono>

RandomInitializer::RandomInitializer()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    gen.seed(seed);
}

RandomInitializer::RandomInitializer(const RandomInitializerConfig& config)
{
    RandomInitializer();
    set_config(config);
}

void RandomInitializer::set_config(const RandomInitializerConfig& config)
{
    this->config = config;
}

inline std::uniform_real_distribution<Real>
_uniform_dist_from_pair(const std::pair<Real, Real>& range)
{
    return std::uniform_real_distribution<Real> (range.first,
    range.second);
}

void RandomInitializer::set_position(Vectors3D& pos, std::size_t body_count) const
{
    auto dist = _uniform_dist_from_pair(config.position_range);
    for(size_t i=0; i<body_count; i++)
    {
        for(uint8_t k=0; k<3; k++)
           pos(i, k) = dist(gen);
    }
}

void RandomInitializer::set_velocity(Vectors3D& vel, std::size_t body_count) const
{
    auto dist = _uniform_dist_from_pair(config.velocity_range);
    for(size_t i=0; i<body_count; i++)
    {
        for(uint8_t k=0; k<3; k++)
        {
            if(config.zero_vel)
                vel(i, k) = 0;
            else
                vel(i, k) = dist(gen);
        }
    }
}

void RandomInitializer::set_mass(Vector& mass, std::size_t body_count) const
{
    auto dist = _uniform_dist_from_pair(config.mass_range);
    for(size_t i=0; i<body_count; i++)
    {
        mass(i) = dist(gen);
    }
}

std::string RandomInitializer::get_name() const
{
    return "Random Initializer";
}