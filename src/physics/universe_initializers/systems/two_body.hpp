#ifndef TWO_BODY_INITIALIZER_HPP_INCLUDED
#define TWO_BODY_INITIALIZER_HPP_INCLUDED

#include "physics/universe_initializers/base_initializer.hpp"
#include "physics/common_types.hpp"
#include "physics/vector_3D.hpp"
#include "config/config_loader.hpp"
#include "exceptions/fatal_error.hpp"
#include <memory>

// Initializer that initializes a simple system with 2 bodies.
// Body 1 is stationary and body 2 is moving areound it.
class TwoBodyInitializer : public UniverseInitializer
{
public:
    TwoBodyInitializer(){}
    TwoBodyInitializer(std::weak_ptr<ConfigurationLoader> config_loader);

    void init(std::weak_ptr<ConfigurationLoader> config_loader) override;

    void set_position(Vectors3D& pos) const override;
    void set_velocity(Vectors3D& vel) const override;
    void set_mass(Vector& mass) const override;
    std::string get_name() const override;

private:
    void enforce_body_count(std::size_t body_count) const;

    Real body1_mass = 1000;
    Real body2_mass = 0.1;
    Vector3D<Real> body2_velocity = {0, 0, 1};
    Vector3D<Real> body2_position = {0, 32, 0};
};

struct TwoBodyInitializerException : public FatalError
{
    TwoBodyInitializerException(const std::string& message):
    FatalError(message)
    {}
};

#endif
