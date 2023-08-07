//
//  app.cpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 07/08/23.
//

#include "process.hpp"
namespace process{
    Process::Process(int width, int height, std::string process_name, bool resizable):
        resizable{resizable},
        process_name{process_name},
        width{width},
        height{height}
    {
        
    };
    
    void Process::run(){
        while (!window.should_close()) {
            glfwPollEvents();
        }
    }
}
