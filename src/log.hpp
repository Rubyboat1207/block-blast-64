/**
 * @file log.hpp
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 * 
 * Copyright (C) 2025 Rubyboat (owner of https://github.com/Rubyboat1207)
 * Copyright (C) 2025 Samuel Stuart
 */

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