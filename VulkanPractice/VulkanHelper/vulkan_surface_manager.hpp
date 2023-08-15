//
//  vulkan_surface_manager.hpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 14/08/23.
//

#ifndef vulkan_surface_manager_hpp
#define vulkan_surface_manager_hpp

#include <stdio.h>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace vulkanHelper{

    struct SwapChainSupportDetails{
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
        
        bool is_adequate(){
            return !formats.empty() && !presentModes.empty();
        }
    };

    class VulkanSurfaceManager{
        private:
            VkSurfaceKHR surface = VK_NULL_HANDLE;
            VkSwapchainKHR swapchain = VK_NULL_HANDLE;
            VkSurfaceFormatKHR surface_format;
            VkPresentModeKHR present_mode;
            VkExtent2D extent;
            std::vector<VkImage> swapchain_images;
            std::vector<VkImageView> swapchain_image_views;
            VkSurfaceFormatKHR choose_surface_format(const std::vector<VkSurfaceFormatKHR> &available_formats);
            VkPresentModeKHR choose_surface_present_mode(const std::vector<VkPresentModeKHR> &available_present_mode);
            VkExtent2D choose_surface_extent(const VkSurfaceCapabilitiesKHR &capabilities, GLFWwindow *window);
        public:
            static SwapChainSupportDetails query_swapchain_support(VkPhysicalDevice device, VkSurfaceKHR surface);
            void create_surface(VkInstance instance,GLFWwindow* window);
            void create_swapchain(VkPhysicalDevice device,VkDevice logical_device, GLFWwindow* window);
            void create_swapchain_image_views(VkDevice logical_device);
            void clean_up(VkInstance instance, VkDevice device);
            VkSurfaceKHR get_surface(){return surface;}
            VkSwapchainKHR get_swapchain() {return swapchain;}
            VkSurfaceFormatKHR get_surface_format(){return surface_format;}
            VkPresentModeKHR get_present_mode(){return present_mode;}
            VkExtent2D get_extent(){return extent;}
            std::vector<VkImage> get_swapchain_images(){return swapchain_images;}
            std::vector<VkImageView> get_swapchain_image_views(){return swapchain_image_views;}
    };
}

#endif
