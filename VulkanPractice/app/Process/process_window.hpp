//
//  app_window.hpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 07/08/23.
//

#ifndef process_window_hpp
#define process_window_hpp
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <string>

namespace process {
    class ProcessWindow{
        public:
            ProcessWindow(int width, int height, std::string name, bool resizable);
            ~ProcessWindow();
            bool should_close(){return glfwWindowShouldClose(window);}
        private:
            void init_window();
            const int width;
            const int height;
            const bool resizable;
            const std::string window_name;
            GLFWwindow *window;
    };
}

#endif /* app_window_hpp */
