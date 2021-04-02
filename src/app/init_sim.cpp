#include "app.hpp"
#include "physics/universe_initializers/universe_initializers.hpp"
#include <spdlog/spdlog.h>

void TinyverseApp::init_simulation()
{
    UniverseConfig universe_config = config_gen.get_universe_config();

    if(universe_config.initializer_type == UniverseConfig::Initializer::TWO_BODY
      && universe_config.universe_size != 2 )
    {
        spdlog::warn("Invalid universe size! Must be = 2 for 2 body initializer, setting to 2 ...");
        universe_config.universe_size = 2;
    }

    universe.set_size(universe_config.universe_size);

    // Build and apply initializer.
    std::shared_ptr<UniverseInitializer> initializer;
    switch(universe_config.initializer_type)
    {
        case UniverseConfig::Initializer::RANDOM:
        initializer = std::make_shared<RandomInitializer>(
            config_gen.get_random_initializer_config(true));
        break;

        case UniverseConfig::Initializer::TWO_BODY:
        initializer = std::make_shared<TwoBodyInitializer>(
            config_gen.get_two_body_initializer_config(true));
        break;
    }

    universe.apply_initializer(initializer);
}
