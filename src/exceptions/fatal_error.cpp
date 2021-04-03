#include "fatal_error.hpp"
#include <spdlog/spdlog.h>

FatalError::FatalError(const std::string& what_arg):
runtime_error(what_arg)
{
    log_error_message();
}

FatalError::FatalError(const char* what_arg):
runtime_error(what_arg)
{
    log_error_message();
}

void FatalError::log_error_message() const
{
    std::string err;
    err += "Exception occured: ";
    err += what();
    spdlog::error(err);
}