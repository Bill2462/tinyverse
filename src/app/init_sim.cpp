#include "app.hpp"
#include "config/json_loader.hpp"
#include <spdlog/spdlog.h>

void TinyverseApp::init_simulation()
{
    if(config_path.empty())
    {
        spdlog::error("No configuration file specified!");
        std::terminate();
    }

    spdlog::info(std::string("Loading configuration file '" + config_path + std::string("'...")));
    auto config_loader = std::make_shared<JsonConfigurationLoader>(config_path);

    spdlog::info("Initializer simulation ....");
    universe.init(config_loader);
}
