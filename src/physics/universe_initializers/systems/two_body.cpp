#include "two_body.hpp"
#include <spdlog/spdlog.h>

TwoBodyInitializer::TwoBodyInitializer(const TwoBodyInitializerConfig& config)
{
    set_config(config);
}

void TwoBodyInitializer::set_config(const TwoBodyInitializerConfig& config)
{
    this->config = config;
}

inline void _enforce_body_count(std::size_t body_count)
{
    if(body_count != 2)
    {
        spdlog::error(std::string("Body count ") +
        std::to_string(body_count) + std::string(" is invalid! Universe size must be 2!"));
        throw(TwoBodyInitializerException("Invalid body count!"));
    }
}

void TwoBodyInitializer::set_position(Vectors3D& pos, std::size_t body_count) const
{
    _enforce_body_count(body_count);
    pos(0, 0) = 0;
    pos(0, 1) = 0;
    pos(0, 2) = 0;
    pos(1, 0) = config.body2_position.x;
    pos(1, 1) = config.body2_position.y;
    pos(1, 2) = config.body2_position.z;
}

void TwoBodyInitializer::set_velocity(Vectors3D& vel, std::size_t body_count) const
{
    _enforce_body_count(body_count);
    vel(0, 0) = 0;
    vel(0, 1) = 0;
    vel(0, 2) = 0;
    vel(1, 0) = config.body2_velocity.x;
    vel(1, 1) = config.body2_velocity.y;
    vel(1, 2) = config.body2_velocity.z;
}

void TwoBodyInitializer::set_mass(Vector& mass, std::size_t body_count) const
{
    _enforce_body_count(body_count);
    mass(0) = config.body1_mass;
    mass(1) = config.body2_mass;
}

std::string TwoBodyInitializer::get_name() const
{
    return "Two Body System Initializer";
}
