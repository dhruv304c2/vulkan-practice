//
//  app.hpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 07/08/23.
//

#ifndef app_hpp
#define app_hpp

#include <stdio.h>
#include "Process/process.hpp"

namespace app{
    class App{
        public:
            static constexpr int width = 800;
            static constexpr int height = 600;
            const std::string app_name = "Vulkan App";
            void run();
        private:
            process::Process main_Process{width,height,app_name};
    };
} 

#endif /* app_hpp */
