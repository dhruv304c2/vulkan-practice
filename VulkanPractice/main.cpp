#include <iostream>
#include "process.hpp"

int main() {
    process::Process app{};
    
    try {
        app.run();
    } catch (const std::exception &c) {
        std::cerr << c.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
