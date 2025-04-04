/**
 * @brief Logging subsystem
 * @author Samuel Stuart (4/4/2025)
 */

#pragma once

#include <stdio.h>
#include <string>
#include <libdragon.h>

/**
 * @brief Log levels
 */
typedef enum {
    DEBUG,      // Debugging information
    INFO,       // Information
    WARN,       // Warnings
    ERROR,      // Errors
} LOG_LEVEL;

namespace Log {

    
    #ifdef __INTELLISENSE__
    /**
     * @brief Write to the debug log (for Ares, in the terminal)
     * @param level The level to log at
     * @param fmt Format string (accepts VA arguments)
     */
    void log(LOG_LEVEL level, const char *fmt, ...);
    #else
    #define log(level, ...) log_internal(level, __FILE__, __LINE__, __PRETTY_FUNCTION__); debugf(__VA_ARGS__)
    #endif
    
    /* Actual logging methods */
    void log_internal(LOG_LEVEL level, std::string file, int line, std::string function);
};