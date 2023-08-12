#include "vulkan_device_manager.hpp"
#include "vulkan_helper.hpp"
#include "log_utility.hpp"

namespace vulkanHelper{
    
    //List of allow device types
    const std::vector<VkPhysicalDeviceType> VulkanDeviceManager::allowed_types = {
        VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU,
        VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU,
        VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU
    };

    const std::vector<VkQueueFlagBits> VulkanDeviceManager::required_queues_flags = {
        VK_QUEUE_GRAPHICS_BIT
    };

    const std::vector<const char*> VulkanDeviceManager::required_extenstion = {
        "VK_KHR_swapchain"
    };

    VkPhysicalDevice VulkanDeviceManager::get_physical_device(){
        if(selected_physical_device != VK_NULL_HANDLE)
            return selected_physical_device;
        select_device();
        return selected_physical_device;
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
                selected_physical_device = device;
                vkGetPhysicalDeviceProperties(device, &properties);
                vkGetPhysicalDeviceFeatures(device, &features);
                break;
            }
        }
        
        if(selected_physical_device == VK_NULL_HANDLE){
            throw std::runtime_error("[Error] failed to find a suitable GPU!");
        }
        
        std::cout << "suitable physical device found successfully" << std::endl;
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
        
        auto queueFamilyIndexMap = find_queue_families(device);
        
        bool geometryShaderTestPassed = (deviceFeatures.geometryShader || !requires_geometry_shader);
        bool suitable = true;
        suitable &= deviceTypeMatched;
        suitable &= geometryShaderTestPassed;
        for(auto flag : required_queues_flags) suitable &= queueFamilyIndexMap[flag].has_value();
        return suitable;
    }

    void VulkanDeviceManager::print_physical_device_details(){
        common::LogUtility::skip(1);
        if(selected_physical_device == VK_NULL_HANDLE ) {
            std::cout << "No device selected" << std::endl;
            return;
        }
        
        std::cout << "Selected device details:-" << std::endl;
        std::cout << "Name: " << properties.deviceName << std::endl;
        std::cout << "Id: " << properties.deviceID << std::endl;
        std::cout << "Device type: " << properties.deviceType << std::endl;
        std::cout << "Vendor Id: " << properties.vendorID << std::endl;
        std::cout << "Driver version: " << properties.driverVersion << std::endl;
        std::cout << "API version: " << properties.apiVersion << std::endl;
        common::LogUtility::skip(1);
    }

    std::map<VkQueueFlagBits,std::optional<uint32_t>> VulkanDeviceManager::find_queue_families(VkPhysicalDevice device){
        
        //initalising output map
        std::map<VkQueueFlagBits,std::optional<uint32_t>> outMap;
        for(auto flags : required_queues_flags){
            outMap[flags] = std::optional<uint32_t>{};
        }
        
        
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device,&queueFamilyCount,queueFamilies.data());
        
        for(auto queueFlags : required_queues_flags){
            int i=0;
            for(auto queueFamily : queueFamilies){
                if(queueFamily.queueFlags & queueFlags){
                    outMap[queueFlags] = i;
                }
                i++;
            }
        }
        return outMap;
    }

    VkDevice VulkanDeviceManager::get_device(){
        if(logical_device != VK_NULL_HANDLE) return logical_device;
        auto queueFamilyIndexMap = find_queue_families(get_physical_device());
        
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamilyIndexMap[VK_QUEUE_GRAPHICS_BIT].value();
        queueCreateInfo.queueCount = 1;
        float queuePriority = 1.0f;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        
        VkPhysicalDeviceFeatures deviceFeatures{};
        
        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = 1;
        createInfo.pQueueCreateInfos = &queueCreateInfo;
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = (uint32_t) required_extenstion.size();
        createInfo.ppEnabledExtensionNames = required_extenstion.data();
        
        if(vkCreateDevice(get_physical_device(), &createInfo, nullptr, &logical_device) != VK_SUCCESS){
            throw  std::runtime_error("[Error] failed to create logical device interface");
        }
        std::cout << "Logical device interface created sucessfully" << std::endl;
        
        vkGetDeviceQueue(logical_device, queueFamilyIndexMap[VK_QUEUE_GRAPHICS_BIT].value(), 0, &graphics_queue);
        return logical_device;
    }

    void VulkanDeviceManager::clean_up(){
        vkDestroyDevice(logical_device, nullptr);
    }
}
