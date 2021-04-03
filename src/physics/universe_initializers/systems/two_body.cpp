#include "two_body.hpp"

void TwoBodyInitializer::enforce_body_count(std::size_t body_count) const
{
    if(body_count != 2)
    {
        throw(TwoBodyInitializerException(std::string("Body count ") +
        std::to_string(body_count) + std::string(" is invalid! Universe size must be 2!")));
    }
}

TwoBodyInitializer::TwoBodyInitializer(std::weak_ptr<ConfigurationLoader> config_loader)
{
    init(config_loader);
}

void TwoBodyInitializer::init(std::weak_ptr<ConfigurationLoader> config_loader)
{
    if(auto ptr = config_loader.lock())
    {
        body1_mass = ptr->get_real("initializer_config", "body1_mass");
        body2_mass = ptr->get_real("initializer_config", "body2_mass");
        body2_position = ptr->get_vector_3D("initializer_config", "body2_position");
        body2_velocity = ptr->get_vector_3D("initializer_config", "body2_velocity");
    }
    else
        throw(TwoBodyInitializerException("Invalid config loader!"));
}

void TwoBodyInitializer::set_position(Vectors3D& pos) const
{
    enforce_body_count(pos.rows());
    pos(0, 0) = 0;
    pos(0, 1) = 0;
    pos(0, 2) = 0;
    pos(1, 0) = body2_position.x;
    pos(1, 1) = body2_position.y;
    pos(1, 2) = body2_position.z;
}

void TwoBodyInitializer::set_velocity(Vectors3D& vel) const
{
    enforce_body_count(vel.rows());
    vel(0, 0) = 0;
    vel(0, 1) = 0;
    vel(0, 2) = 0;
    vel(1, 0) = body2_velocity.x;
    vel(1, 1) = body2_velocity.y;
    vel(1, 2) = body2_velocity.z;
}

void TwoBodyInitializer::set_mass(Vector& mass) const
{
    enforce_body_count(mass.rows());
    mass(0) = body1_mass;
    mass(1) = body2_mass;
}

std::string TwoBodyInitializer::get_name() const
{
    return "Two Body System Initializer";
}
