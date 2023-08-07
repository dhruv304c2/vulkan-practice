//
//  app_window.cpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 07/08/23.
//
#include "process_window.hpp"

namespace process{
    ProcessWindow::ProcessWindow(int width, int height, std::string window_name, bool resizable) :
        width{width},
        height{height},
        window_name{window_name},
        resizable{resizable}
    {
        ProcessWindow::init_window();
    }
        
    ProcessWindow::~ProcessWindow(){
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void ProcessWindow::init_window(){
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //No API as we are not using Open Gl
        if(!resizable) glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        
        window = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
    }

}
