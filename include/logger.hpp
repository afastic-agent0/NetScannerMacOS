#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

enum class LogLevel {
    INFO,
    WARN,
    ERROR
};

class Logger {
public:
    static void log(LogLevel level, const std::string& message);
    static void info(const std::string& message) { log(LogLevel::INFO, message); }
    static void warn(const std::string& message) { log(LogLevel::WARN, message); }
    static void error(const std::string& message) { log(LogLevel::ERROR, message); }
};

#endif // LOGGER_HPP
