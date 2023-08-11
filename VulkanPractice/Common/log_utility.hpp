//
//  log_utility.hpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 11/08/23.
//

#ifndef log_utility_hpp
#define log_utility_hpp

#include <stdio.h>
#include <string>
namespace common{
    class LogUtility{
        public:
            void static log_green_text(const std::string text);
            void static skip(const uint32_t lines);
    };
}

#endif /* log_utility_hpp */
