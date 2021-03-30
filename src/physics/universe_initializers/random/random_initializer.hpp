#ifndef RANDOM_INITIALIZER_HPP_INCLUDED
#define  RANDOM_INITIALIZER_HPP_INCLUDED

#include "physics/universe_initializers/base_initializer.hpp"
#include "physics/common_types.hpp"
#include <random>

class RandomInitializer : public UniverseInitializer
{
public:
    struct Config
    {
        std::pair<Real, Real> position_range;
        std::pair<Real, Real> velocity_range;
        std::pair<Real, Real> mass_range;

        bool zero_vel = true;
        bool zero_mass = true; 
    };
    
    RandomInitializer();
    
    void set_config(const Config& config);

    void set_position(Vectors3D& pos, std::size_t body_count) const override;
    void set_velocity(Vectors3D& vel, std::size_t body_count) const override;
    void set_mass(Vector& mass, std::size_t body_count) const override;
    std::string get_name() const override;

private:
    Config config;
    mutable std::mt19937 gen;
};

#endif
