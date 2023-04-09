#include "say-hello.hpp"

#include <iostream>

void SayHello(const std::string& name) noexcept {
    std::cout << "Hello, " << name;
}