#include "logger.hpp"
#include <iostream>
#include <string>

void Logger::log(LogLevel level, const std::string& message) {
    std::string prefix;
    switch (level) {
        case LogLevel::INFO:  prefix = "[INFO] ";  break;
        case LogLevel::WARN:  prefix = "[WARN] ";  break;
        case LogLevel::ERROR: prefix = "[ERROR] "; break;
    }

    if (level == LogLevel::ERROR) {
        std::cerr << prefix << message << std::endl;
    } else {
        std::cout << prefix << message << std::endl;
    }
}
