#include <iostream>
#include "app.hpp"

int main() {
    app::App app{};
    
    try {
        app.run();
    } catch (const std::exception &c) {
        std::cerr << c.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
