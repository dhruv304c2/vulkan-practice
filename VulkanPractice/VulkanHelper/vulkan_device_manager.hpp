#ifndef vulkan_device_manager_hpp
#define vulkan_device_manager_hpp

#include <stdio.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>

namespace vulkanHelper{
    class VulkanDeviceManager{
        private:
            VkPhysicalDevice selected_device = VK_NULL_HANDLE;
            VkPhysicalDeviceProperties properties;
            VkPhysicalDeviceFeatures features;
            void select_device();
            void set_device_details();
            static bool device_selected;
            static const std::vector<VkPhysicalDeviceType> allowed_types;
            static const bool requires_geometry_shader = false;
            bool is_device_suitable(VkPhysicalDevice device);
        public:
            VkPhysicalDevice get_device();
            void print_device_details();
            VkPhysicalDeviceFeatures get_features(){return features;}
            VkPhysicalDeviceProperties get_properties(){return properties;}
    };
};

#endif
