//
//  app_window.hpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 07/08/23.
//

#ifndef app_window_hpp
#define app_window_hpp
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <string>

namespace app {
    class AppWindow{
        public:
            AppWindow(int width, int height, std::string name);
            ~AppWindow();
            bool should_close(){return glfwWindowShouldClose(window);}
        private:
            void init_window();
            const int width;
            const int height;
            std::string window_name;
            GLFWwindow *window;
    };
}

#endif /* app_window_hpp */
