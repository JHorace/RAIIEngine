// Created 2022
// James Sumihiro and Bryan Johnson
//

#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1

#include <iostream>

#include "engine_defaults.hpp"
#include "engine_vk.hpp"

VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

namespace Forge
{
  //bool IsPhysicalDeviceSuitable(vk::raii::PhysicalDevice const & physDevice)
  //{
  //  vk::PhysicalDeviceProperties properties = physDevice.getProperties();
  //  vk::PhysicalDeviceFeatures features = physDevice.getFeatures();
  //
  //  return (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu);
  //}
  //
  //vk::raii::PhysicalDevice ChoosePhysicalDevice(vk::raii::Instance const & instance)
  //{
  //  auto physDevices = instance.enumeratePhysicalDevices();
  //
  //  for (auto const & physDevice: physDevices)
  //    if (IsPhysicalDeviceSuitable(physDevice))
  //      return physDevice;
  //}
  
  EngineVK::EngineVK(std::vector<const char *> extensions,
                     std::vector<const char *> layers)
    :
    _vkContext{},
    _vkInstance{CreateInstance(_vkContext, extensions, layers)},
    _deviceManager{_vkInstance}
  {
    // Create a DeviceManager for each physical device.
    vk::raii::PhysicalDevices physDevices{_vkInstance};
    for (auto & physicalDevice : physDevices)
      _deviceManagers.emplace_back(DeviceManager(physicalDevice));
    
    const std::vector<const char *> device_extensions{DEFAULT_DEVICE_EXTENSIONS.begin(), DEFAULT_DEVICE_EXTENSIONS.end()};
    _deviceManagers[0].AddLogicalDevice(device_extensions, layers);
  }
  
  void EngineVK::Render()
  {
  
  }
  
  void EngineVK::AddWindow(void * windowHandle)
  {
    //_renderers.push_back(Renderer());
  }
  
  vk::raii::Context CreateContext()
  {
    return vk::raii::Context{};
  }
  
  bool EngineVK::CheckValidationLayerSupport(std::vector<const char *> const & validationLayers)
  {
    auto availableInstanceLayers = _vkContext.enumerateInstanceLayerProperties();
    
    for (const auto & requiredLayer: validationLayers)
    {
      bool found = false;
      
      for (const auto & availableLayer: availableInstanceLayers)
        if (strcmp(requiredLayer, availableLayer.layerName) == 0)
          found = true;
      
      if (!found)
        return false;
    }
    
    return true;
  }
  
}