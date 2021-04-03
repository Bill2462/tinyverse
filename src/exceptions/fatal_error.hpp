#ifndef FATAL_ERROR_EXCEPTION_HPP
#define FATAL_ERROR_EXCEPTION_HPP

#include <stdexcept>

// Fatal error is an exception that is also printing error
// message to the console.
class FatalError : public std::runtime_error
{
public:
    FatalError(const std::string& what_arg);
    FatalError(const char* what_arg);

private:
    void log_error_message() const;
};

#endif
