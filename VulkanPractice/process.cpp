//
//  app.cpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 07/08/23.
//

#include "process.hpp"
namespace process{
    
    void Process::run(){
        while (!window.should_close()) {
            glfwPollEvents();
        }
    }
}
