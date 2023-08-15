#include "app.hpp"
#include <iostream>
#include "vulkan_helper.hpp"

using namespace vulkanHelper;

namespace app{
    
    void App::run(){
        std::cout << "Running.. " << app_name << std::endl;
        VulkanHelper::get_instance() -> initalise_vulkan(app_name, main_process.get_window());
        main_process.run();
    }

    bool App::is_running(){
        return main_process.is_running;
    }

    void App::clean_up(){
        VulkanHelper::get_instance() -> clean_up();
    }
}
