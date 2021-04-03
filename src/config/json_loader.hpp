#ifndef JSON_CONFIG_LOADER_HPP_INCLUDED
#define JSON_CONFIG_LOADER_HPP_INCLUDED

#include "config/config_loader.hpp"
#include <string>
#include <nlohmann/json.hpp>
#include "exceptions/fatal_error.hpp"

class JsonConfigurationLoader : public ConfigurationLoader
{
public:
    JsonConfigurationLoader(){}
    JsonConfigurationLoader(const std::string& filepath);

    void load_file(const std::string& filepath);
    
    std::size_t get_integer(const std::string& module_name, const std::string& param_name) const override;
    Real get_real(const std::string& module_name, const std::string& param_name) const override;
    std::string get_string(const std::string& module_name, const std::string& param_name) const override;
    std::pair<Real, Real> get_pair(const std::string& module_name, const std::string& param_name) const override;
    Vector3D<Real> get_vector_3D(const std::string& module_name, const std::string& param_name) const override;
    bool get_bool(const std::string& module_name, const std::string& param_name) const override;
    bool has_parameter(const std::string&  module_name, const std::string& param_name) const override;

private:
    void ensure_parameter_exists(const std::string& module_name, const std::string& param_name) const;

    nlohmann::json parsed_config;
    std::string filepath;
};

struct JsonConfigurationLoaderException : public FatalError
{
    JsonConfigurationLoaderException(const std::string& message,
                                     const std::string& filename):
    FatalError(std::string("Error occured while loading file: '" ) + filename + 
    std::string("'! ") + message)
    {}
};

#endif
