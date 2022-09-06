//
// Created by James on 8/27/2022.
//

#include "../include/engine_vk.hpp"
#include <iostream>

#ifndef NDEBUG
#include "debug.hpp"
#endif

vk::raii::Instance CreateInstance(vk::raii::Context const & context,
                                  std::vector<const char *> instanceLayers,
                                  std::vector<const char *> instanceExtensions);

vk::raii::PhysicalDevice ChoosePhysicalDevice(vk::raii::Instance const& instance, vk::raii::PhysicalDevices const& physDevices);

bool IsPhysicalDeviceSuitable(vk::raii::PhysicalDevice const& physDevice);

vk::raii::Device CreateDevice(vk::raii::PhysicalDevice const& physDevice,
                              std::vector<const char *> deviceExtensions,
                              std::vector<const char *> deviceLayers);

uint32_t FindQueueFamily(vk::raii::PhysicalDevice const& physDevice);




Forge::EngineVK::EngineVK()
: _instance(CreateInstance(_context, std::vector<const char *>(), std::vector<const char *>()))
, _physDevice(ChoosePhysicalDevice(_instance, vk::raii::PhysicalDevices(_instance)))
{
    std::cout << "NoCopy member initialization successful" << std::endl;
}

void Forge::EngineVK::Render() {

}

vk::raii::Instance CreateInstance(vk::raii::Context const & context, std::vector<const char *> instanceLayers, std::vector<const char *> instanceExtensions)
{
    vk::ApplicationInfo appInfo{
            .pApplicationName = "test",
            .applicationVersion = 1,
            .pEngineName = "test",
            .engineVersion = 1,
            .apiVersion = VK_API_VERSION_1_3,
    };

    vk::InstanceCreateInfo instanceCI{
            .pApplicationInfo = &appInfo,
            .enabledLayerCount = (uint32_t)instanceLayers.size(),
            .ppEnabledLayerNames = instanceLayers.data(),
            .enabledExtensionCount = (uint32_t)instanceExtensions.size(),
            .ppEnabledExtensionNames = instanceExtensions.data(),
    };

    return {vk::raii::Instance(context, instanceCI)};

}

vk::raii::PhysicalDevice ChoosePhysicalDevice(vk::raii::Instance const& instance, vk::raii::PhysicalDevices const& physDevices)
{
    for(auto const & physDevice : physDevices)
    {
        if(IsPhysicalDeviceSuitable(physDevice))
            return physDevice;
    }
}

bool IsPhysicalDeviceSuitable(vk::raii::PhysicalDevice const& physDevice)
{
    vk::PhysicalDeviceProperties properties = physDevice.getProperties();
    vk::PhysicalDeviceFeatures features = physDevice.getFeatures();

    return (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu);




}


vk::raii::Device CreateDevice(vk::raii::PhysicalDevice const& physDevice,
                              std::vector<const char *> deviceExtensions,
                              std::vector<const char *> deviceLayers)
{
  return vk::raii::Device(nullptr);
}

uint32_t FindQueueFamily(vk::raii::PhysicalDevice const& physDevice)
{
    auto queueFamilyProperties = physDevice.getQueueFamilyProperties();

    for (uint32_t i = 0; i < queueFamilyProperties.size(); ++i)
        if (queueFamilyProperties[i].queueFlags & (vk::QueueFlagBits::eGraphics | vk::QueueFlagBits::eCompute))
            return i;

    return 0;
}


