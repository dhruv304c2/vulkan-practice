//
//  app.hpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 07/08/23.
//

#ifndef process_hpp
#define process_hpp

#include <stdio.h>
#include "process_window.hpp"

namespace process{
    class Process{
        public:
            Process(int width = 800, int height = 600, std::string process_name = "new Process", bool resizable = false);
            bool resizable;
            const int width;
            const int height;
            const std::string process_name;
            void run();
        private:
            ProcessWindow window{width,height,process_name, resizable};
    };
}
#endif /* app_hpp */
