#include <string>
#include <fstream>
#include <streambuf>
#include "json_loader.hpp"

using json = nlohmann::json;

JsonConfigurationLoader::JsonConfigurationLoader(const std::string& filepath)
{
    load_file(filepath);
}

void JsonConfigurationLoader::ensure_parameter_exists(const std::string& module_name,
                                                      const std::string& param_name) const
{
    if(!parsed_config.contains(module_name))
    {
        throw(JsonConfigurationLoaderException(std::string("Module '")+
        module_name+std::string("' not found"), filepath));
    }

    if(!parsed_config[module_name].contains(param_name))
    {
        throw(JsonConfigurationLoaderException(std::string("Parameter '")+
        param_name+std::string("' not found"), filepath));
    }
}

void JsonConfigurationLoader::load_file(const std::string& filepath)
{
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
        throw(JsonConfigurationLoaderException("IO error", filepath));
    }
    catch(const json::exception& e)
    {
        throw(JsonConfigurationLoaderException("Parser error", filepath));
    }

    this->filepath = filepath;
}

std::size_t JsonConfigurationLoader::get_integer(const std::string& module_name, const std::string& param_name) const
{
    ensure_parameter_exists(module_name, param_name);

    return parsed_config[module_name][param_name].get<std::size_t>();
}

Real JsonConfigurationLoader::get_real(const std::string& module_name, const std::string& param_name) const
{
    ensure_parameter_exists(module_name, param_name);

    Real value;

    value = parsed_config[module_name][param_name].get<Real>();
    if(!isfinite(value))
    {
        throw(JsonConfigurationLoaderException(std::string("Parameter '")+
        param_name+std::string("' is not finite"), filepath));
    }

    return value;
}

std::string JsonConfigurationLoader::get_string(const std::string& module_name, const std::string& param_name) const
{
    ensure_parameter_exists(module_name, param_name);

    return parsed_config[module_name][param_name].get<std::string>();
}

std::pair<Real, Real> JsonConfigurationLoader::get_pair(const std::string& module_name, const std::string& param_name) const
{
    ensure_parameter_exists(module_name, param_name);

    std::pair<Real, Real> value;
    
    const std::size_t size = parsed_config[module_name][param_name].size();
    if(size != 2)
    {
        throw(JsonConfigurationLoaderException(std::string("Parameter '")+
        param_name+std::string("' expected size is 2 but got") + std::to_string(size), filepath));
    }

    value.first = parsed_config[module_name][param_name][0].get<Real>();
    value.second = parsed_config[module_name][param_name][1].get<Real>();
    
    if(!(isfinite(value.first) && isfinite(value.second)))
    {
        throw(JsonConfigurationLoaderException(std::string("Parameter '")+
        param_name+std::string("' is not finite"), filepath));
    }

    return value;
}

Vector3D<Real> JsonConfigurationLoader::get_vector_3D(const std::string& module_name, const std::string& param_name) const
{
    ensure_parameter_exists(module_name, param_name);

    Vector3D<Real> value;
    
    const std::size_t size = parsed_config[module_name][param_name].size();
    if(size != 3)
    {
        throw(JsonConfigurationLoaderException(std::string("Parameter '")+
        param_name+std::string("' expected size is 3 but got") + std::to_string(size), filepath));
    }

    value.x = parsed_config[module_name][param_name][0].get<Real>();
    value.y = parsed_config[module_name][param_name][1].get<Real>();
    value.z = parsed_config[module_name][param_name][2].get<Real>();
    
    if(!(isfinite(value.x) && isfinite(value.y) && isfinite(value.z)))
    {
        throw(JsonConfigurationLoaderException(std::string("Parameter '")+
        param_name+std::string("' is not finite"), filepath));
    }

    return value;
}

bool JsonConfigurationLoader::get_bool(const std::string& module_name, const std::string& param_name) const
{
    ensure_parameter_exists(module_name, param_name);
    
    return parsed_config[module_name][param_name].get<bool>();
}

bool JsonConfigurationLoader::has_parameter(const std::string& module_name, const std::string& param_name) const
{
    if(!parsed_config.contains(module_name))
        return false;

    if(!parsed_config[module_name].contains(param_name))
        return false;
    
    return true;
}
