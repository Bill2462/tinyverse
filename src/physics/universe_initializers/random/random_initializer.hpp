#ifndef RANDOM_INITIALIZER_HPP_INCLUDED
#define  RANDOM_INITIALIZER_HPP_INCLUDED

#include "physics/universe_initializers/base_initializer.hpp"
#include "physics/common_types.hpp"
#include "config/config.hpp"
#include <random>

class RandomInitializer : public UniverseInitializer
{
public:
    RandomInitializer();
    RandomInitializer(const RandomInitializerConfig& config);
    
    void set_config(const RandomInitializerConfig& config);

    void set_position(Vectors3D& pos, std::size_t body_count) const override;
    void set_velocity(Vectors3D& vel, std::size_t body_count) const override;
    void set_mass(Vector& mass, std::size_t body_count) const override;
    std::string get_name() const override;

private:
    RandomInitializerConfig config;
    mutable std::mt19937 gen;
};

#endif
