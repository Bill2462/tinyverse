#ifndef DISC_INITIALIZER_HPP_INCLUDED
#define DISC_INITIALIZER_HPP_INCLUDED

#include "physics/universe_initializers/base_initializer.hpp"
#include "physics/common_types.hpp"
#include "physics/vector_3D.hpp"
#include "config/config_loader.hpp"
#include "exceptions/fatal_error.hpp"
#include <memory>
#include <random>

// Disc initializer initializes a massive center body and a disc of smaller bodies orbiting around.
class DiscInitializer : public UniverseInitializer
{
public:
    DiscInitializer();
    DiscInitializer(std::weak_ptr<ConfigurationLoader> config_loader);

    void init(std::weak_ptr<ConfigurationLoader> config_loader) override;

    void set_position(Vectors3D& pos) const override;
    void set_velocity(Vectors3D& vel) const override;
    void set_mass(Vector& mass) const override;
    std::string get_name() const override;

private:
    std::pair<Real, Real> radius_range;
    std::pair<Real, Real> mass_range;
    Real center_mass;
    Real G;

    void generate_bodies(std::size_t size) const;

    // Order is arbitrary so we need to generate bodies before we call set_position.
    mutable bool bodies_generated = false;

    mutable Vectors3D positions;
    mutable Vectors3D velocities;
    mutable Vector masses;

    mutable std::mt19937 gen;
};

struct DiscInitializerInitializerException : public FatalError
{
    DiscInitializerInitializerException(const std::string& message):
    FatalError(message)
    {}
};

#endif
