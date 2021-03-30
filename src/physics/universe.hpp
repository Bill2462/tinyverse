#ifndef UNIVERSE_HPP_INCLUDED
#define UNIVERSE_HPP_INCLUDED

#include <string>
#include <functional>
#include <memory>
#include "physics/common_types.hpp"
#include "universe_initializers/universe_initializers.hpp"

class Universe
{
public:
    Universe(){};
    Universe(size_t n);
    
    // Set amount of bodies that are in the universe.
    void set_size(size_t n);
    size_t get_size() const;

    // Return a reference for accessing positions.
    const Vectors3D& positions() const;

    // Apply initializer 
    void apply_initializer(std::weak_ptr<UniverseInitializer> initializer);

private:
    size_t size = 0;
    Vectors3D position;
    Vectors3D velocity;
    Vector mass;
};

#endif
