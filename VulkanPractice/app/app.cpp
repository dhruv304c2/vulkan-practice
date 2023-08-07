//
//  app.cpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 07/08/23.
//

#include "app.hpp"
#include <iostream>

namespace app{
    void App::run(){
        std::cout << "Running " << app_name;
        main_Process.run();
    }
}
