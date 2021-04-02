#ifndef CONFIG_GENERATOR_HPP_INCLUDED
#define CONFIG_GENERATOR_HPP_INCLUDED

#include "config/config.hpp"

class ConfigurationGenerator
{
public:

    void parse_file(const std::string& filepath);

    UniverseConfig get_universe_config(bool allow_default=false) const;
    SimulationConfig get_sim_config(bool allow_default=false) const;
    RandomInitializerConfig get_random_initializer_config(bool allow_default=false) const;
    TwoBodyInitializerConfig get_two_body_initializer_config(bool allow_default=false) const;

private:
    bool file_loaded = false;
    UniverseConfig universe_config;
    SimulationConfig simulation_config;
    RandomInitializerConfig random_initializer_config;
    TwoBodyInitializerConfig two_body_initializer_config;
};

#endif