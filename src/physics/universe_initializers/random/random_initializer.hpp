#ifndef RANDOM_INITIALIZER_HPP_INCLUDED
#define RANDOM_INITIALIZER_HPP_INCLUDED

#include "physics/universe_initializers/base_initializer.hpp"
#include "physics/common_types.hpp"
#include "config/config_loader.hpp"
#include "exceptions/fatal_error.hpp"
#include <random>

class RandomInitializer : public UniverseInitializer
{
public:
    RandomInitializer();
    RandomInitializer(std::weak_ptr<ConfigurationLoader> config_loader);

    void init(std::weak_ptr<ConfigurationLoader> config_loader) override;

    void set_position(Vectors3D& pos) const override;
    void set_velocity(Vectors3D& vel) const override;
    void set_mass(Vector& mass) const override;
    std::string get_name() const override;

private:
    std::pair<Real, Real> position_range = {-10, 10};
    std::pair<Real, Real> mass_range = {0.01, 50};
    std::pair<Real, Real> velocity_range;
    bool zero_velocity = true;

    mutable std::mt19937 gen;
};

struct RandomInitializerException : public FatalError
{
    RandomInitializerException(const std::string& message):
    FatalError(message)
    {}
};

#endif
