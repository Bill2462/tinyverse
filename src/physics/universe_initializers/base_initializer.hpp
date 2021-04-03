#ifndef UNIVERSE_BASE_INITIALIZER_HPP_INCLUDED
#define UNIVERSE_BASE_INITIALIZER_HPP_INCLUDED

#include <memory>
#include <string>
#include "physics/common_types.hpp"
#include "config/config_loader.hpp"

struct UniverseInitializer
{
    virtual void init(std::weak_ptr<ConfigurationLoader> config_loader) = 0;
    virtual void set_position(Vectors3D& pos) const = 0;
    virtual void set_velocity(Vectors3D& vel) const = 0;
    virtual void set_mass(Vector& mass) const = 0;
    virtual std::string get_name() const = 0;

    enum class Type
    {
        TWO_BODY_SYSTEM,
        RANDOM_INITIALIZER
    };

    static std::shared_ptr<UniverseInitializer> build_and_configure(
    Type type, std::weak_ptr<ConfigurationLoader> config_loader);

    virtual ~UniverseInitializer() = default;
};

#endif
