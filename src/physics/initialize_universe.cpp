#include <spdlog/spdlog.h>
#include "universe.hpp"
#include "universe_initializers/universe_initializers.hpp"
#include "physics/gravity/naive/naive_solver.hpp"

void Universe::init(std::weak_ptr<ConfigurationLoader> config_loader)
{
    if(auto ptr = config_loader.lock())
    {
        size = ptr->get_integer("simulation_config", "universe_size");
        timestep = ptr->get_real("simulation_config", "timestep");
        G = ptr->get_real("simulation_config", "G");
        use_softening = ptr->get_bool ("simulation_config", "use_softening");

        if(use_softening)
            softening_epsilon = ptr->get_real("simulation_config", "softening_epsilon");
        
        std::shared_ptr<UniverseInitializer> initializer;

        const std::string initializer_str = ptr->get_string("simulation_config", "initialier");
        if(initializer_str == "TWO_BODY_SYSTEM")
            initializer = UniverseInitializer::build_and_configure(UniverseInitializer::Type::TWO_BODY_SYSTEM, config_loader);
        else if(initializer_str == "RANDOM_INITIALIZER")
            initializer = UniverseInitializer::build_and_configure(UniverseInitializer::Type::RANDOM_INITIALIZER, config_loader);
        else
            throw(UniverseException("Invalid universe initializer name."));

        set_size(size);

        initializer->set_position(position);
        initializer->set_velocity(velocity);
        initializer->set_mass(mass);

        gravity_solver = std::make_shared<NaiveGravitySolver>(position, mass, G, use_softening, softening_epsilon);

        // Initialize accelerations.
        for(std::size_t i=0; i<get_size(); i++)
        {
            Vector3D<Real> forces = gravity_solver->compute_net_grawitational_force(i);
            acceleration(i, 0) = forces.x/mass(i);
            acceleration(i, 1) = forces.y/mass(i);
            acceleration(i, 2) = forces.z/mass(i);
        }

        spdlog::info(std::string("Universe initialized succesfully using: ") + initializer->get_name());
    }
    else
        throw(UniverseException("Invalid configuration loader."));
}
