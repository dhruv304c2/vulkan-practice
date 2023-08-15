#include <iostream>
#include "App/app.hpp"

int main() {
    auto app = app::App::get_instance();
    try {
        app -> run();
    } catch (const std::exception &c) {
        std::cerr << c.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    app -> clean_up();
    delete app;
    return EXIT_SUCCESS;
}
