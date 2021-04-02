
// This code is not very scalable and contains a lot of boilerplate.
// But it will work for now.
// Also no validation because who needs it!

#include "config_generator.hpp"
#include <string>
#include <fstream>
#include <streambuf>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

using json = nlohmann::json;

inline bool _try_to_find_with_message(const json& config, const std::string& name)
{
    if(config.contains(name))
    {
        spdlog::debug(name + std::string(" found in config!"));
        return true;
    }
    
    spdlog::debug(name + std::string(" not found in config!"));

    return false;
}

inline void _load_universe_config(const json& config, UniverseConfig& output)
{
    if(!_try_to_find_with_message(config, "universe_config"))
        return;

    output.default_config = false;

    auto cfg = config["universe_config"];
    const std::string initializer_type_str = cfg["initializer_type"].get<std::string>();
    if(initializer_type_str == "RANDOM_INITIALIZER")
        output.initializer_type = UniverseConfig::Initializer::RANDOM;
    else if(initializer_type_str == "TWO_BODY")
        output.initializer_type = UniverseConfig::Initializer::TWO_BODY;
    
    output.universe_size = cfg["universe_size"].get<long long>();
}

inline void _load_simulation_config(const json& config,SimulationConfig& output)
{
    if(!_try_to_find_with_message(config, "simulation_config"))
        return;

    auto cfg = config["simulation_config"];
    output.timestep = cfg["timestep"].get<Real>();
    output.G = cfg["G"].get<Real>();
    output.default_config = false;
}

inline std::pair<Real, Real> _parse_pair(const json& pair)
{
   std::pair<Real, Real> output;
   output.first = pair[0].get<Real>();
   output.second = pair[1].get<Real>();

   return output;
}

inline Vector3D<Real> _parse_vector3d(const json& vec)
{
    Vector3D<Real> output;
    output.x = vec[0].get<Real>();
    output.y = vec[1].get<Real>();
    output.z = vec[2].get<Real>();
    return output;
}

inline bool _is_finite(const std::pair<Real, Real>& val)
{
    return std::isfinite(val.first) && std::isfinite(val.second);
}

inline bool _is_finite(const Vector3D<Real>& val)
{
    return std::isfinite(val.x) &&
    std::isfinite(val.y) && std::isfinite(val.z);
}

inline void _load_random_initializer_config(const json& config, RandomInitializerConfig& output)
{
    if(!_try_to_find_with_message(config, "random_initializer_config"))
        return;
    
    auto cfg = config["random_initializer_config"];
    output.position_range = _parse_pair(cfg["position_range"]);

    if(cfg.contains(std::string{"zero_vel"}))
        output.zero_vel = cfg["zero_vel"].get<bool>();
    else
        output.zero_vel = false;
    
    if(!output.zero_vel)
        output.velocity_range = _parse_pair(cfg["velocity_range"]);
    
    output.mass_range = _parse_pair(cfg["mass_range"]);

    output.default_config = false;
}

inline void _load_two_body_initializer_config(const json& config, TwoBodyInitializerConfig& output)
{
    if(!_try_to_find_with_message(config, "two_body_initializer_config"))
        return;

    auto cfg = config["two_body_initializer_config"];
    
    output.body1_mass = cfg["body1_mass"].get<Real>();
    output.body2_mass = cfg["body2_mass"].get<Real>();
    output.body2_velocity = _parse_vector3d(cfg["body2_velocity"]);
    output.body2_position = _parse_vector3d(cfg["body2_position"]);
    output.default_config = false;
}

void ConfigurationGenerator::parse_file(const std::string& filepath)
{
    
    json parsed_config;
    try
    {
        std::ifstream file;
        std::string json_string;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        file.open(filepath);

        std::stringstream str_stream;
        str_stream<<file.rdbuf();
        json_string = str_stream.str();
        file.close();

        parsed_config = json::parse(json_string);
    }
    catch(const std::ifstream::failure& e)
    {
        spdlog::error(std::string("IO error occured while loading '")+
        filepath+std::string("' ")+std::string(e.what())+std::string(" ! Falling back to default config!"));
    }
    catch(const json::exception& e)
    {
        spdlog::error(std::string("Error occured while parsing '")+
        filepath+std::string("' ")+std::string(e.what())+std::string(" ! Falling back to default config!"));
    }
    
    file_loaded = true;
    
    spdlog::debug(std::string("Configuration file '")+
    filepath+std::string("' loaded succesfully!"));

    _load_universe_config(parsed_config, universe_config);
    _load_simulation_config(parsed_config, simulation_config);
    _load_random_initializer_config(parsed_config, random_initializer_config);
    _load_two_body_initializer_config(parsed_config, two_body_initializer_config);
}
