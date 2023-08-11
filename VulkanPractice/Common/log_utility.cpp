//
//  log_utility.cpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 11/08/23.
//

#include "log_utility.hpp"
#include <iostream>

namespace common{
    void LogUtility::log_green_text(const std::string text){
        //system("Color 0A");
        std::cout << text; //Does nothing needs to be implemented
        //system("Color 0E");
    }
    void LogUtility::skip(const uint32_t lines){
        auto l = lines;
        while (l--) {
            std::cout << std::endl;
        }
    }
}
