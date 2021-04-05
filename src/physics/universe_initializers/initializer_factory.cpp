#include "base_initializer.hpp"
#include "universe_initializers.hpp"

std::shared_ptr<UniverseInitializer> UniverseInitializer::build_and_configure
(UniverseInitializer::Type type, std::weak_ptr<ConfigurationLoader> config_loader)
{
    switch(type)
    {
        case UniverseInitializer::Type::TWO_BODY_SYSTEM:
        return std::make_shared<TwoBodyInitializer>(config_loader);

        case UniverseInitializer::Type::RANDOM_INITIALIZER:
        return std::make_shared<RandomInitializer>(config_loader);

        case UniverseInitializer::Type::DISC:
        return std::make_shared<DiscInitializer>(config_loader);
    }

    return std::shared_ptr<UniverseInitializer>(nullptr);
}
