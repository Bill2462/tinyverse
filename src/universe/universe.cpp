#include "universe.hpp"
#include <chrono>
#include <random>

using namespace universe;

void universe::random_universe_initializer(Universe& universe,
const RandomInitializerConfig& config)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);

    std::uniform_real_distribution<Real> pos_dist(config.position_range.first,
    config.position_range.second);

    std::uniform_real_distribution<Real> vel_dist(config.velocity_range.first,
    config.velocity_range.second);

    std::uniform_real_distribution<Real> mass_dist(config.mass_range.first,
    config.mass_range.second);

    for(size_t i=0; i<universe.nbody; i++)
    {
        for(uint8_t k=0; k<3; k++)
        {
            universe.position(i, k) = pos_dist(gen);
            universe.velocity(i, k) = vel_dist(gen);
        }
        universe.mass(i) = mass_dist(gen);
    }
}
