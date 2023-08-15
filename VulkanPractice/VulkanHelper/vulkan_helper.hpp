#pragma once
#ifndef vulkan_helper_hpp
#define vulkan_helper_hpp

#include <iostream>
#include <vulkan/vulkan.h>
#include "generic_singleton.hpp"
#include <string>
#include <vector>
#include "vulkan_device_manager.hpp"
#include "vulkan_surface_manager.hpp"
//#include <optional>

namespace vulkanHelper{

    class VulkanHelper : public common::GenericSingleton<VulkanHelper>{
        public:
            static VkInstance get_vkInstance();
            void initalise_vulkan(const std::string app_name, GLFWwindow *window);
            void clean_up();
        private:
            void create_instance(const std::string app_name);
            bool check_validation_layer_support();
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
            VulkanDeviceManager deviceManager{};
            VulkanSurfaceManager surfaceManager{};
    };
}

#endif
