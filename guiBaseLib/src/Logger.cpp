#include "guiBase/Logger.h"

#include <iostream>

// Color 	                        Foreground 	    Background
//
// Black 	                        \033[30m 	    \033[40m
// Red    	                        \033[31m 	    \033[41m
// Green 	                        \033[32m 	    \033[42m
// Orange 	                        \033[33m 	    \033[43m
// Blue 	                        \033[34m 	    \033[44m
// Magenta 	                        \033[35m 	    \033[45m
// Cyan 	                        \033[36m 	    \033[46m
// Light gray 	                    \033[37m 	    \033[47m
// Fallback to distro's default 	\033[39m     	\033[49m

namespace guiBase {
    LogLevel Logger::logLevel = LogLevel::trace;

    std::string LogLevelStr(LogLevel level) {
        std::string str = "";
        switch (level) {
        case LogLevel::none:
            str = "none";
            break;
        case LogLevel::critical:
            str = "critical";
            break;
        case LogLevel::error:
            str = "error";
            break;
        case LogLevel::warning:
            str = "warning";
            break;
        case LogLevel::info:
            str = "info";
            break;
        case LogLevel::trace:
            str = "trace";
            break;
        default:
            str = "[INVALID]";
            break;
        }

        return str;
    }

    void Logger::critical(const std::string_view str) {
        if (logLevel >= LogLevel::critical) {
            // 41 red bg, 37 white fg
            print(str, "\033[41;37m[CRITICAL]: ");
        }
    }

    void Logger::error(const std::string_view str) {
        if (logLevel >= LogLevel::error) {
            // 31 red fg, 40 black bg
            print(str, "\033[31;40m[ERROR]: ");
        }
    }

    void Logger::warning(const std::string_view str) {
        if (logLevel >= LogLevel::warning) {
            // 33 yellow fg, 40 black bg
            print(str, "\033[33;40m[warning]: ");
        }
    }

    void Logger::info(const std::string_view str) {
        if (logLevel >= LogLevel::info) {
            // 36 cyan fg, 40 black bg
            print(str, "\033[36;40m[info]: ");
        }
    }

    void Logger::trace(const std::string_view str) {
        if (logLevel >= LogLevel::trace) {
            // 33 light gray fg, 40 black bg
            print(str, "\033[33;40m[trace]: ");
        }
    }

    void Logger::setLogLevel(const LogLevel& level) {
        LOG_INFO(std::string("changing logLevel from ") + LogLevelStr(logLevel) + " -> " + LogLevelStr(level));
        logLevel = level;
    }

    void Logger::print(const std::string_view str, std::string_view col, std::string_view reset) {
        std::cout << col << str << reset << '\n';
    }
}// namespace guiBase
