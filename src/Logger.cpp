#include "Logger.h"
#include <iostream>

static const char* logLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARN: return "WARN";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

void Logger::log(LogLevel level, 
    const std::string& component,
    const std::string& message) {
    std::cout << "[" << logLevelToString(level) << "] "
              << "[" << component << "] "
              << message << std::endl;
}