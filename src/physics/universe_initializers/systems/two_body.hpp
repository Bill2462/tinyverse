#ifndef TWO_BODY_INITIALIZER_HPP_INCLUDED
#define TWO_BODY_INITIALIZER_HPP_INCLUDED

#include "physics/universe_initializers/base_initializer.hpp"
#include "physics/common_types.hpp"
#include "physics/vector_3D.hpp"

#include <exception>

// Initializer that initializes a simple system with 2 bodies.
// Body 1 is stationary and body 2 is moving areound it.
class TwoBodyInitializer : public UniverseInitializer
{
public:
    struct Config
    {
        Real body1_mass = 100;
        Real body2_mass = 1;
        Vector3D<Real> body2_velocity;
        Vector3D<Real> body2_position;
    };
    
    void set_config(const Config& config);

    void set_position(Vectors3D& pos, std::size_t body_count) const override;
    void set_velocity(Vectors3D& vel, std::size_t body_count) const override;
    void set_mass(Vector& mass, std::size_t body_count) const override;
    std::string get_name() const override;

private:
    Config config;
};

class TwoBodyInitializerException : public std::exception
{
public:
    explicit TwoBodyInitializerException(const char* message) noexcept:
    msg(message)
    {}

    const char* what() const noexcept
    {
        return msg;
    }
    
private:
    const char* msg;
};

#endif
