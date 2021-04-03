#ifndef CONFIG_LOADER_HPP_INCLUDED
#define CONFIG_LOADER_HPP_INCLUDED

#include "physics/common_types.hpp"
#include "physics/vector_3D.hpp"

#include <utility>

struct ConfigurationLoader
{
    virtual std::size_t get_integer(const std::string& module_name, const std::string& param_name) const = 0;
    virtual Real get_real(const std::string&  module_name, const std::string& param_name) const = 0;
    virtual std::string get_string(const std::string&  module_name, const std::string& param_name) const = 0;
    virtual std::pair<Real, Real> get_pair(const std::string&  module_name, const std::string& param_name) const = 0;
    virtual Vector3D<Real> get_vector_3D(const std::string&  module_name, const std::string& param_name) const = 0;
    virtual bool get_bool(const std::string& module_name, const std::string& param_name) const = 0;
    virtual bool has_parameter(const std::string&  module_name, const std::string& param_name) const = 0;

    virtual ~ConfigurationLoader() = default;
};

#endif