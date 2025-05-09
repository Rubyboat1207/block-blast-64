/**
 * @file log.cpp
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
 * @brief Logging class
 * @author Samuel Stuart (4/4/2025)
 */
#include <string>
#include "log.hpp"

namespace Log {

    /**
     * @brief Cleans up GCC's __PRETTY_FUNCTION__
     * 
     * For a method defined as main GCC gives __PRETTY_FUNCTION__ as "int main()"
     */
    static std::string fixupClassname(std::string prettyFunction) {
        size_t method_name_start = prettyFunction.find_last_of(' ') + 1;
        size_t method_name_end = prettyFunction.find('(');
        return prettyFunction.substr(method_name_start, method_name_end - method_name_start);
    }

    /**
     * @brief Internal log method
     */
    void log_internal(LOG_LEVEL level, std::string file, int line, std::string function) {
        // Fixup __PRETTY_FUNCTION__
        std::string fn_fixed = fixupClassname(function);

        // Convert log level to string
        std::string log_level_str;
        switch (level) {
            case DEBUG:
                log_level_str = "DEBUG";
                break;
            
            case INFO:
                log_level_str = "INFO ";
                break;

            case ERROR:
                log_level_str = "ERROR";
                break;

            case WARN:
                log_level_str = "WARN";
                break;
        }

        // Print it out
        // log macro will then print the user input
        debugf("[%s] (%s:%d) (%s) ", log_level_str.c_str(), file.c_str(), line, fn_fixed.c_str());
    }
}