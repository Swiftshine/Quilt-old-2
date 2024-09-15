#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

namespace AppLog {
    template <typename T>
    void Print(const T& t) {
        std::cout << t;
        std::cout << "\n";
    }

    template <typename T, typename... Args>
    void Print(const T& t, const Args&... args) {
        std::cout << t;
        Print(args...);
    }

    template <typename T>
    inline void Error(const T& t) {
        std::cerr << "Quilt error: " << t;
        std::cerr << "\n";
        throw std::runtime_error(t);
    }

    template <typename T, typename... Args>
    inline void Error(const T& t, const Args&... args) {
        std::cerr << "Quilt error: " << t;
        Print(args...);
        throw std::runtime_error(t);
    }

    static void Assert(bool condition, std::string msg) {
        if (!condition) {
            std::cerr << "Quilt assertion failed: " << msg << "\n";
            std::abort();
        }
    }
}
