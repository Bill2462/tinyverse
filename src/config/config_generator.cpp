#include "config/config_generator.hpp"
#include <string>
#include <spdlog/spdlog.h>

inline void _warn_about_default_settings(bool allow_default, bool default_flag, 
const std::string& config_name)
{
    if(!allow_default && default_flag)
    {
        spdlog::warn(std::string("Requested configuration ('") + config_name +
        std::string("') not found in the file! Falling back to default configuration!"));
    }
}

UniverseConfig ConfigurationGenerator::get_universe_config(bool allow_default) const
{
    if(file_loaded)
        _warn_about_default_settings(allow_default, universe_config.default_config, "Universe Config");
    
    return universe_config;
}

SimulationConfig ConfigurationGenerator::get_sim_config(bool allow_default) const
{
    if(file_loaded)
        _warn_about_default_settings(allow_default, simulation_config.default_config, "Simulation Config");

    return simulation_config;
}

RandomInitializerConfig ConfigurationGenerator::get_random_initializer_config(bool allow_default) const
{
    if(file_loaded)
     _warn_about_default_settings(allow_default, random_initializer_config.default_config, "Random Initializer Config");

    return random_initializer_config;
}

TwoBodyInitializerConfig ConfigurationGenerator::get_two_body_initializer_config(bool allow_default) const
{
    if(file_loaded)
        _warn_about_default_settings(allow_default, two_body_initializer_config.default_config, "Two Body Initializer Config");

    return two_body_initializer_config;
}
