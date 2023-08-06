//
//  app_window.cpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 07/08/23.
//
#include "app_window.hpp"

namespace app{
    AppWindow::AppWindow(int width, int height, std::string window_name) :
        width{width},
        height{height},
        window_name{window_name}
    {
        AppWindow::init_window();
    }
        
    AppWindow::~AppWindow(){
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void AppWindow::init_window(){
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //No API as we are not using Open Gl
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //Need another way to handle window resizing
        
        window = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
    }

}
