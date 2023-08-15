//
//  vulkan_surface_manager.cpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 14/08/23.
//

#include "vulkan_surface_manager.hpp"
#include <iostream>
#include <limits>
#include <algorithm>
#include "vulkan_device_manager.hpp"
namespace vulkanHelper{
    
        SwapChainSupportDetails VulkanSurfaceManager::query_swapchain_support(VkPhysicalDevice device, VkSurfaceKHR surface){
        SwapChainSupportDetails details{};
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);
        
        uint32_t formatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
        
        uint32_t presentModeCount = 0;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
        
        return details;
    }

    void VulkanSurfaceManager::create_surface(VkInstance instance, GLFWwindow* window){
        if(glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS){
            throw std::runtime_error("[Error] failed to create window surface");
        }
        
        std::cout << "\nsurface created successfully" << std::endl;
    }

    VkSurfaceFormatKHR VulkanSurfaceManager::choose_surface_format(const std::vector<VkSurfaceFormatKHR> &available_formats){
        for(auto availableFormat : available_formats){
            if(availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR){
                return availableFormat;
            }
        }
        
        return available_formats[0]; //Fallback incase required format is not found
    }

    VkPresentModeKHR VulkanSurfaceManager::choose_surface_present_mode(const std::vector<VkPresentModeKHR> &available_present_mode){
        for(auto availablePresentMode : available_present_mode){
            if(availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR){
                return availablePresentMode;
            }
        }
        
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D VulkanSurfaceManager::choose_surface_extent(const VkSurfaceCapabilitiesKHR &capabilities, GLFWwindow *window){
        if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max() ){
            return capabilities.currentExtent; //if true means you are now allowed to differ from current values
        }
        else{
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            
            VkExtent2D actualExtent =
            {
                (uint32_t) width,
                (uint32_t) height
            };
            
            actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
            actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.width);
            
            return actualExtent;
        }
    };

    void VulkanSurfaceManager::create_swapchain(VkPhysicalDevice device,VkDevice logical_device, GLFWwindow *window){
        SwapChainSupportDetails swapChainSupport = query_swapchain_support(device, surface);
        
        surface_format = choose_surface_format(swapChainSupport.formats);
        present_mode = choose_surface_present_mode(swapChainSupport.presentModes);
        extent = choose_surface_extent(swapChainSupport.capabilities, window);
        
        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
        
        if(swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount){
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }
            VkSwapchainCreateInfoKHR createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
            createInfo.surface = surface;
            createInfo.minImageCount = imageCount;
            createInfo.imageFormat = surface_format.format;
            createInfo.imageColorSpace = surface_format.colorSpace;
            createInfo.imageExtent = extent;
            createInfo.imageArrayLayers = 1;
            createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
            
            QueueFamilyIndices indices = VulkanDeviceManager::find_queue_families(device, surface);
            uint32_t queueFamilyIndices[] = {indices.graphics_family.value(), indices.present_family.value()};

            if (indices.graphics_family != indices.present_family) {   //If queues are not same
                createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
                createInfo.queueFamilyIndexCount = 2;
                createInfo.pQueueFamilyIndices = queueFamilyIndices;
            } else {                                                    //If queues are same
                createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
                createInfo.queueFamilyIndexCount = 0; // Optional
                createInfo.pQueueFamilyIndices = nullptr; // Optional
            }
            createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
            createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
            createInfo.presentMode = present_mode;
            createInfo.clipped = VK_TRUE;
            
            if(vkCreateSwapchainKHR(logical_device, &createInfo, nullptr, &swapchain) != VK_SUCCESS){
                throw std::runtime_error("[Error] failed to create swap chain");
            }
            
            std::cout << "swap chain created successfully" << std::endl;
        
            vkGetSwapchainImagesKHR(logical_device, swapchain, &imageCount, nullptr);
            swapchain_images.resize(imageCount);
            vkGetSwapchainImagesKHR(logical_device, swapchain, &imageCount, swapchain_images.data());
    }

    void VulkanSurfaceManager::create_swapchain_image_views(VkDevice logical_device){
        swapchain_image_views.resize(swapchain_images.size());
        
        for(int i=0; i < swapchain_images.size(); i++){
            VkImageViewCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image = swapchain_images[i];
            createInfo.format = surface_format.format;
            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1;
            
            if(vkCreateImageView(logical_device, &createInfo, nullptr, &swapchain_image_views[i]) != VK_SUCCESS){
                throw std::runtime_error("[Error] failed to create image view for an image");
            }
            
            std::cout << "image views created successfully" << std::endl;
        }
    }

    void VulkanSurfaceManager::clean_up(VkInstance instance, VkDevice device){
        std::cout << "surface manager performing clean up" <<std::endl;
        vkDestroySurfaceKHR(instance, surface, nullptr);
        std::cout << "surface destroyed" <<std::endl;
        vkDestroySwapchainKHR(device, swapchain, nullptr);
        std::cout << "swapchain destroyed" <<std::endl;
        std::cout << "all swapchain images destroyed" <<std::endl;
        for(auto imageView: swapchain_image_views){
            vkDestroyImageView(device, imageView, nullptr);
        }
        std::cout << "all swapchain image views destroyed" <<std::endl;
    }
}
