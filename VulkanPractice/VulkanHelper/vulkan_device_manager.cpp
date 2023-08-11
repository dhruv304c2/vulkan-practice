//
//  vulkan_device_manager.cpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 12/08/23.
//

#include "vulkan_device_manager.hpp"
#include "vulkan_helper.hpp"

namespace vulkanHelper{
    
    //List of allow device types
    const std::vector<VkPhysicalDeviceType> VulkanDeviceManager::allowed_types = {
        VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU,
        VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU,
        VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU
    };

    bool VulkanDeviceManager::device_selected = false;

    VkPhysicalDevice VulkanDeviceManager::get_device(){
        if(selected_device != VK_NULL_HANDLE)
            return selected_device;
        select_device();
        return selected_device;
    }

    void VulkanDeviceManager::select_device(){
        uint32_t deviceCount = 0;
        VkInstance vk = VulkanHelper::get_vkInstance();
        vkEnumeratePhysicalDevices(vk, &deviceCount, nullptr);
        if(deviceCount == 0){
            throw std::runtime_error("[Error] failed to find GPUs with Vulkan support!");
        }
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(vk, &deviceCount, devices.data());
        for(auto device : devices){
            if(is_device_suitable(device)){
                selected_device = device;
                vkGetPhysicalDeviceProperties(device, &properties);
                vkGetPhysicalDeviceFeatures(device, &features);
                device_selected = true;
                break;
            }
        }
        
        if(selected_device == VK_NULL_HANDLE){
            throw std::runtime_error("[Error] failed to find a suitable GPU!");
        }
        
        std::cout << "suitable device found successfully" << std::endl;
    }

    bool VulkanDeviceManager::is_device_suitable(VkPhysicalDevice device){
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
        
        bool deviceTypeMatched = false;
        for(auto type : allowed_types){
            if(deviceProperties.deviceType == type){
                deviceTypeMatched = true;
                break;
            }
        }
        
        bool geometryShaderTestPassed = (deviceFeatures.geometryShader || !requires_geometry_shader);
        bool suitable = true;
        suitable &= deviceTypeMatched;
        suitable &= geometryShaderTestPassed;
        return suitable;
    }

    void VulkanDeviceManager::print_device_details(){
        if(!device_selected) {
            std::cout << "No device selected" << std::endl;
            return;
        }
        
        std::cout << "Selected device details" << std::endl;
        std::cout << "Name: " << properties.deviceName << std::endl;
        std::cout << "Id: " << properties.deviceID << std::endl;
        std::cout << "Device type: " << properties.deviceType << std::endl;
        std::cout << "Vendor Id: " << properties.vendorID << std::endl;
        std::cout << "Driver version: " << properties.driverVersion << std::endl;
        std::cout << "API version: " << properties.apiVersion << std::endl;
    }
}
