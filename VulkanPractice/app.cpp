//
//  app.cpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 07/08/23.
//

#include "app.hpp"
namespace app{
    
    void App::run(){
        while (!app_window.should_close()) {
            glfwPollEvents();
        }
    }
}
