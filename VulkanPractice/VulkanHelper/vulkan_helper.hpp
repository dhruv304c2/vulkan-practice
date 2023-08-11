#pragma once
#ifndef vulkan_helper_hpp
#define vulkan_helper_hpp

#include <stdio.h>
#include <vulkan/vulkan.h>
#include "generic_singleton.hpp"
#include <string>
#include <vector>

namespace vulkanHelper{

    class VulkanHelper : public common::GenericSingleton<VulkanHelper>{
        public:
            ~VulkanHelper(){clean_up();}
            static VkInstance get_vkInstance();
            void initalise_vulkan(const std::string app_name);
        private:
            void create_instance(const std::string app_name);
            bool check_validation_layer_support();
            void clean_up();
            void print_all_extensions();
            
            const std::vector<const char*> added_validation_layers = {
                "VK_LAYER_KHRONOS_validation"
            };
#ifdef NDEBUG
            bool enabledValidationLayers = false;
#else
            bool enabledValidationLayers = true;
#endif
            VkInstance instance;
            VkPhysicalDevice physical_device = VK_NULL_HANDLE;
    };
}

#endif
