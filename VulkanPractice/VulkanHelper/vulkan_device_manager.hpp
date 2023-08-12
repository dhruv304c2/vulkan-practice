#ifndef vulkan_device_manager_hpp
#define vulkan_device_manager_hpp

#include <stdio.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include <map>

namespace vulkanHelper{

    class VulkanDeviceManager{
        private:
            VkPhysicalDevice selected_physical_device = VK_NULL_HANDLE;
            VkPhysicalDeviceProperties properties;
            VkPhysicalDeviceFeatures features;
            VkDevice logical_device = VK_NULL_HANDLE;
            VkQueue graphics_queue;
            static const std::vector<const char*> required_extenstion;
            static const std::vector<VkPhysicalDeviceType> allowed_types;
            static const std::vector<VkQueueFlagBits> required_queues_flags;
            static const bool requires_geometry_shader = false;
            void select_device();
            void set_device_details();
            std::map<VkQueueFlagBits, std::optional<uint32_t>> find_queue_families(VkPhysicalDevice device);
            bool is_device_suitable(VkPhysicalDevice device);
            void clean_up();
        public:
            ~VulkanDeviceManager(){clean_up();}
            VkPhysicalDevice get_physical_device();
            VkDevice get_device();
            void print_physical_device_details();
            VkPhysicalDeviceFeatures get_features(){return features;}
            VkPhysicalDeviceProperties get_properties(){return properties;}
            VkQueue get_graphics_queue(){return graphics_queue;}
    };
};

#endif
