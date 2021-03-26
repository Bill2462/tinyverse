#include "log.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <string>
#include "config.h"

const char* BANNER = "\n"
"d888888P oo                                                                \n"
"   88                                                                      \n"
"   88    dP 88d888b. dP    dP dP   .dP .d8888b. 88d888b. .d8888b. .d8888b. \n"
"   88    88 88   `88 88    88 88   d8  88ooood8 88'  `88 Y8ooooo. 88ooood8 \n"
"   88    88 88    88 88.  .88 88 .88   88.  ... 88             88 88.  ... \n"
"   dP    dP dP    dP `8888P88 8888P    `88888P' dP       `88888P' `88888P' \n"
"                          .88                                              \n"
"                      d8888P                                               \n";

// Print configuration into the console.
void log_configuration(sf::ContextSettings window_settings)
{
    spdlog::info(BANNER);
    spdlog::info(std::string("Welcome to Tinyverse version ") +
                 std::to_string(PROJECT_VERSION_MAJOR) + 
                 std::string(".") +
                 std::to_string(PROJECT_VERSION_MINOR) +
                 "!");

    spdlog::info(std::string("Found OpenGL version ") +
                 std::to_string(window_settings.majorVersion) +
                 std::string(".") +
                 std::to_string(window_settings.minorVersion));

    spdlog::debug("### Window configuration ###");

    spdlog::debug(std::string("Depth bits: ") + 
                 std::to_string(window_settings.depthBits));
    
    spdlog::debug(std::string("Stencil bits: ") + 
                 std::to_string(window_settings.stencilBits));
    
    spdlog::debug(std::string("Antyaliasing level: ") + 
                 std::to_string(window_settings.antialiasingLevel));
}
