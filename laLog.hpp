#pragma once
#include <iostream>
#include <sstream>

namespace la {

    enum LogLevel {
        ERROR,
        WARN,
        INFO,
        DEBUG
    };

    static inline void log(LogLevel level, const std::string& message)
    {
        switch (level)
        {
        case LogLevel::DEBUG:
            std::cout << "[DEBUG]: " << message << std::endl;
            break;
        case LogLevel::INFO:
            std::cout << "[INFO]: " << message << std::endl;
            break;
        case LogLevel::WARN:
            std::cout << "[WARNING]: " << message << std::endl;
            break;
        case LogLevel::ERROR:
            std::cout << "[ERROR]: " << message << std::endl;
            break;
        default:
            std::cout << message << std::endl;
        }
    }

    static inline void setLogLevel(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::DEBUG:
            std::cout << "Logger initialized with Debug level" << std::endl;
            break;
        case LogLevel::INFO:
            std::cout << "Logger initialized with Info level" << std::endl;
            break;
        case LogLevel::WARN:
            std::cout << "Logger initialized with Warning level" << std::endl;
            break;
        case LogLevel::ERROR:
            std::cout << "Logger initialized with Error level" << std::endl;
            break;
        }
    }


    template <typename T>
    std::string toString(const T& value)
    {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }
}