//
//  app.cpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 07/08/23.
//

#include "process.hpp"
#include <ctime>
#include <iostream>

namespace process{
    Process::Process(int width, int height, std::string process_name, bool resizable):
        resizable{resizable},
        process_name{process_name},
        width{width},
        height{height}
    {
    };
    
    unsigned int Process::get_process_run_time(){
        time_t currentTime;
        std::time(&currentTime);
        
        return (unsigned int)(currentTime - start_time);
    }

    void Process::run(){
        is_running = true;
        std::time(&start_time); // setting start time
        while (!window.should_close()) {
            glfwPollEvents();
        }
        is_running = false;
        float runTime = get_process_run_time();
        std::cout << process_name <<" Process ended in time: " << runTime << " seconds" << std::endl;
    }

    GLFWwindow* Process::get_window(){
        return window.get_window();
    }
}
