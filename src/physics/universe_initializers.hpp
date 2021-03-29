#ifndef UNIVERSE_INITIALIZERS_HPP_INCLUDED
#define UNIVERSE_INITIALIZERS_HPP_INCLUDED

#include <utility>
#include "common_types.hpp"
#include "universe.hpp"

struct RandomInitializerConfig
{
    std::pair<Real, Real> position_range;
    std::pair<Real, Real> velocity_range;
    std::pair<Real, Real> mass_range;
};

void random_universe_initializer(Universe& universe, const RandomInitializerConfig& config);

#endif
