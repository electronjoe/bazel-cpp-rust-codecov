#include "greeter.h"

#include <cassert>
#include <iostream>

int main() {
    assert(greet("World") == "Hello, World!");
    assert(greet("Bazel") == "Hello, Bazel!");
    std::cout << "All tests passed." << std::endl;
    return 0;
}
