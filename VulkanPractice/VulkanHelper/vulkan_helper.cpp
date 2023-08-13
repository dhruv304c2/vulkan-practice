#include "vulkan_helper.hpp"
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <cstring>
#include "log_utility.hpp"
#include "vulkan_device_manager.hpp"

namespace vulkanHelper{

    VkInstance VulkanHelper::get_vkInstance(){
        return get_instance() -> instance;
    }

    void VulkanHelper::initalise_vulkan(const std::string app_name, GLFWwindow* window){
        create_instance(app_name);
        print_all_extensions();
        //creating window surface
        deviceManager.create_surface(instance, window);
        
        //selecting physical device
        deviceManager.get_physical_device();
        deviceManager.print_physical_device_details();
        
        //creating logical device
        deviceManager.get_device();
    }

    void VulkanHelper::clean_up(){
        vkDestroyInstance(get_vkInstance(), nullptr);
        std::cout << "Performing vulkan clean up" << std::endl;
    }

    void VulkanHelper::create_instance(const std::string app_name){
        
        common::LogUtility::skip(1);
        std::cout << "Initialisng Vulkan...." << std::endl;
        
        if(enabledValidationLayers && !check_validation_layer_support()){
            throw std::runtime_error("[Error] unsupported validation layer added");
        }
    
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
        
        //Enabling validation layers
        if(enabledValidationLayers){
            createInfo.enabledLayerCount = static_cast<uint32_t>(added_validation_layers.size());
            createInfo.ppEnabledLayerNames = added_validation_layers.data();
        }
        createInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("[Error] failed to create instance!");
        }
        
        std::cout << "Vulkan initialisation completed successfully" << std::endl;
    }

    void VulkanHelper::print_all_extensions(){
        common::LogUtility::skip(3);
        
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        
        std::cout << "All instance extensions: " << std::endl;
        for(int i=0; i< extensionCount; i++){
            std::cout << extensions[i].extensionName << std::endl;
        }
        
        common::LogUtility::skip(3);
    }

    bool VulkanHelper::check_validation_layer_support(){
        common::LogUtility::skip(3);
        
        uint32_t availableLayerCount = 0;
        vkEnumerateInstanceLayerProperties(&availableLayerCount, nullptr);
        std::vector<VkLayerProperties> availableLayers(availableLayerCount);
        vkEnumerateInstanceLayerProperties(&availableLayerCount, availableLayers.data());
        
        std::cout << "Available validation layers:" << std::endl;
        for(const char* layerName: added_validation_layers){
            bool found = false;
            for(auto availableLayer: availableLayers){
                std::cout << availableLayer.layerName;
                if(strcmp(availableLayer.layerName, layerName) == 0){
                    found = true;
                    common::LogUtility::log_green_text(" (required)");
                }
                std::cout << std::endl;
            }
            if(!found){
                return false;
            }
        }
        
        common::LogUtility::skip(3);
        return true;
    }
}
