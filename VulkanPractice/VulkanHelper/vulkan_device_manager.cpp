#include "vulkan_device_manager.hpp"
#include "vulkan_helper.hpp"
#include "log_utility.hpp"
#include "vulkan_surface_manager.hpp"
#include <set>

namespace vulkanHelper{
    
    //List of allow device types
    const std::vector<VkPhysicalDeviceType> VulkanDeviceManager::allowed_types = {
        VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU,
        VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU,
        VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU
    };

    const std::vector<const char*> VulkanDeviceManager::device_extenstions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    VkPhysicalDevice VulkanDeviceManager::get_physical_device(){
        return selected_physical_device;
    }

    void VulkanDeviceManager::select_device(VkSurfaceKHR surface){
        uint32_t deviceCount = 0;
        VkInstance vk = VulkanHelper::get_vkInstance();
        vkEnumeratePhysicalDevices(vk, &deviceCount, nullptr);
        if(deviceCount == 0){
            throw std::runtime_error("[Error] failed to find GPUs with Vulkan support!");
        }
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(vk, &deviceCount, devices.data());
        for(auto device : devices){
            if(is_device_suitable(device,surface)){
                selected_physical_device = device;
                vkGetPhysicalDeviceProperties(device, &properties);
                vkGetPhysicalDeviceFeatures(device, &features);
                break;
            }
        }
        
        if(selected_physical_device == VK_NULL_HANDLE){
            throw std::runtime_error("[Error] failed to find a suitable GPU!");
        }
        
        std::cout << "\nsuitable physical device found successfully" << std::endl;
    }

    bool VulkanDeviceManager::is_device_suitable(VkPhysicalDevice device, VkSurfaceKHR surface){
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
        uint32_t extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());
        
        //creating a set and removing found extensions from it, if all are found set should be empty
        //at the end of the loop
        std::set<std::string> requiredExtensions(device_extenstions.begin(),device_extenstions.end());
        std::cout << "\navilable device extensions:- " << std::endl;
        for(auto extension : availableExtensions){
            requiredExtensions.erase(extension.extensionName);
            std::cout << extension.extensionName << std::endl;
        }
        
        //Logging all the extensions not found
        if(!requiredExtensions.empty()){
            std::cout << "\ndevice extensions not found:- " << std::endl;
            for(auto requiredExtensionName: requiredExtensions){
                std::cout << requiredExtensionName << std::endl;
            }
        }
        
        // finding queue family indicies
        auto queueFamilyIndices= find_queue_families(device, surface);
        
        // getting swap chain support details
        auto swapChainSupportDetails = VulkanSurfaceManager::query_swapchain_support(device,surface);
        
        bool geometryShaderTestPassed = (deviceFeatures.geometryShader || !requires_geometry_shader);
        bool suitable = true;
        suitable &= deviceTypeMatched;
        suitable &= geometryShaderTestPassed;
        suitable &= queueFamilyIndices.has_all();
        suitable &= swapChainSupportDetails.is_adequate();
        suitable &= requiredExtensions.empty();
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

    QueueFamilyIndices VulkanDeviceManager::find_queue_families(VkPhysicalDevice device, VkSurfaceKHR surface){
        
        //initalising output
        QueueFamilyIndices queueFamilyIndices{};
        
        
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device,&queueFamilyCount,queueFamilies.data());
        
        int i=0;
        for(auto queueFamily : queueFamilies){
            if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT){
                queueFamilyIndices.graphics_family = i;
            }
            
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
            if(presentSupport){
                queueFamilyIndices.present_family = i;
            }
            i++;
        }
        
        return queueFamilyIndices;
    }

    VkDevice VulkanDeviceManager::get_device(){
        return logical_device;
    }

    void VulkanDeviceManager::create_logical_device(VkSurfaceKHR surface){
        auto queueFamilyIndices = find_queue_families(get_physical_device(), surface);
        
        
        //device queue creation
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::vector<uint32_t> families = {queueFamilyIndices.graphics_family.value(), queueFamilyIndices.present_family.value()};
        
        for(auto familyIndex : families){
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = familyIndex;
            queueCreateInfo.queueCount = 1;
            float queuePriority = 1.0f;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }
        
        //enabled device features
        VkPhysicalDeviceFeatures deviceFeatures{};
        
        //logical device creation
        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = (uint32_t) queueCreateInfos.size();
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = (uint32_t) device_extenstions.size();
        createInfo.ppEnabledExtensionNames = device_extenstions.data();
        
        if(vkCreateDevice(get_physical_device(), &createInfo, nullptr, &logical_device) != VK_SUCCESS){
            throw  std::runtime_error("[Error] failed to create logical device interface");
        }
        std::cout << "logical device interface created sucessfully" << std::endl;
        
        //getting device queue handles
        vkGetDeviceQueue(logical_device, queueFamilyIndices.graphics_family.value(), 0, &graphics_queue);
        vkGetDeviceQueue(logical_device, queueFamilyIndices.present_family.value(), 0, &presentation_queue);
    }
}
