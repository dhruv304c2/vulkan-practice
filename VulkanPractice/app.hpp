//
//  app.hpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 07/08/23.
//

#ifndef app_hpp
#define app_hpp

#include <stdio.h>
#include "app_window.hpp"

namespace app{
    class App{
        public:
            static constexpr int width = 800;
            static constexpr int height = 600;
            void run();
        private:
            AppWindow app_window{width,height,"Hello vulkan!"};
    };
}
#endif /* app_hpp */
