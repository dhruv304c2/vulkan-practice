#ifndef vulkan_device_manager_hpp
#define vulkan_device_manager_hpp

#include <stdio.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include <map>
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//#define GLFW_EXPOSE_NATIVE_WIN32
//#include <GLFW/glfw3native.h>

namespace vulkanHelper{

    struct QueueFamilyIndices{
        std::optional<uint32_t> graphics_family;
        std::optional<uint32_t> present_family;
        
        bool has_all(){
            return graphics_family.has_value() && present_family.has_value();
        }
    };

    class VulkanDeviceManager{
        private:
            VkPhysicalDevice selected_physical_device = VK_NULL_HANDLE;
            VkPhysicalDeviceProperties properties;
            VkPhysicalDeviceFeatures features;
            VkDevice logical_device = VK_NULL_HANDLE;
            VkQueue graphics_queue;
            VkQueue presentation_queue;
            static const std::vector<const char*> device_extenstions;
            static const std::vector<VkPhysicalDeviceType> allowed_types;
            static const bool requires_geometry_shader = false;
            void set_device_details();
            bool is_device_suitable(VkPhysicalDevice device, VkSurfaceKHR surface);
        public:
            void select_device(VkSurfaceKHR surface);
            VkPhysicalDevice get_physical_device();
            void create_logical_device(VkSurfaceKHR surface);
            VkDevice get_device();
            void print_physical_device_details();
            VkPhysicalDeviceFeatures get_features(){return features;}
            VkPhysicalDeviceProperties get_properties(){return properties;}
            VkQueue get_graphics_queue(){return graphics_queue;}
            VkQueue get_presentation_queue(){return presentation_queue;}
        
            static QueueFamilyIndices find_queue_families(VkPhysicalDevice device, VkSurfaceKHR surface);
    };
};

#endif
