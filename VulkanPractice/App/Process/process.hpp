//
//  app.hpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 07/08/23.
//

#ifndef process_hpp
#define process_hpp

#include <stdio.h>
#include <ctime>
#include "process_window.hpp"
#include <GLFW/glfw3.h>

namespace process{
    class Process{
        public:
        Process(int width = 800, int height = 600, std::string process_name = "new Process", bool resizable = false);
            bool resizable;
            const int width;
            const int height;
            const std::string process_name;
            bool is_running = false;
            void run();
            unsigned int get_process_run_time();
            GLFWwindow* get_window();
        private:
            ProcessWindow window{width,height,process_name, resizable};
            time_t start_time;
    };
}
#endif /* app_hpp */
