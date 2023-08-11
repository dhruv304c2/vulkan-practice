#include "vulkan_helper.hpp"
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

namespace vulkanHelper{

    void VulkanHelper::clean_up(){
        vkDestroyInstance(get_vkInstance(), nullptr);
        std::cout << "Performing vulkan clean up" << std::endl;
    }

    void VulkanHelper::create_instance(const std::string app_name){
            
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = app_name.data();
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;
    
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
    
        uint32_t glfwExtensionsCount = 0;
        const char** glfwExtensions;
        std::vector<const char*> requiredExtensions;
    
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);
        for(int i=0; i < glfwExtensionsCount; i++){
            requiredExtensions.emplace_back(glfwExtensions[i]);
        }
    
        requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME); //To fix an error while working on macOS
        createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR; //To fix an error while working on macOS
        createInfo.enabledExtensionCount = (uint32_t) requiredExtensions.size();
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();
        createInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
    
        //Logging available vK extensions
        uint32_t extensionCount = 0;
        std::vector<VkExtensionProperties> extensions;
        
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        
        //std::cout << "All instance extension name" << std::endl;
        for(int i=0; i< extensionCount; i++){
            //Commneted out because giving errors...
            //std::cout << extensions[i].extensionName << std::endl;
        }
    }
}
