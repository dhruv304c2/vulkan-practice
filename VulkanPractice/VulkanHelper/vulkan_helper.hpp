#pragma once
#ifndef vulkan_helper_hpp
#define vulkan_helper_hpp

#include <stdio.h>
#include <vulkan/vulkan.h>
#include "generic_singleton.hpp"
#include <string>

namespace vulkanHelper{

    class VulkanHelper : public common::GenericSingleton<VulkanHelper>{
        public:
            ~VulkanHelper(){clean_up();}
            VkInstance get_vkInstance(){return instance;}
            void create_instance(const std::string app_name);
            void clean_up();
        private:
            VkInstance instance;
    };
}

#endif
