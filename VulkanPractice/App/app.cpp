//
//  app.cpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 07/08/23.
//

#include "app.hpp"
#include <iostream>
#include "vulkan_helper.hpp"

using namespace vulkanHelper;

namespace app{
    
    void App::run(){
        std::cout << "Running.. " << app_name << std::endl;
        VulkanHelper::get_instance() -> create_instance(app_name);
        main_process.run();
    }

    bool App::is_running(){
        return main_process.is_running;
    }
}
