// Created 2022
// James Sumihiro and Bryan Johnson
//

#define VULKAN_HPP_TYPESAFE_CONVERSION 1

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_vulkan.h"

#include "engine_defaults.hpp"
#include "engine_vk.hpp"


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
    _vkInstance{_vkContext, CIBuilder(&appInfo, extensions, layers)}
  {
    // Create a DeviceManager for each physical device.
    vk::raii::PhysicalDevices physDevices{_vkInstance};
    for (auto & physicalDevice: physDevices)
      _deviceManagers.emplace_back(DeviceManager(physicalDevice));
    
    const std::vector<const char *> device_extensions{DEFAULT_DEVICE_EXTENSIONS.begin(), DEFAULT_DEVICE_EXTENSIONS.end()};
    _deviceManagers[0].AddLogicalDevice(device_extensions, layers);
  }
  
  void EngineVK::Render()
  {
  
  }
  
  
  vk::InstanceCreateInfo EngineVK::CIBuilder(const vk::ApplicationInfo * appInfo,
                                             std::vector<const char *> & extensions,
                                             std::vector<const char *> & layers)
  {
    if (DEBUG_LOGGING)
    {
      // Add debug layers and extensions
      layers.insert(layers.end(), DEBUG_LAYERS.begin(), DEBUG_LAYERS.end());
      extensions.insert(extensions.end(), DEBUG_EXTENSIONS.begin(), DEBUG_EXTENSIONS.end());
      
      CheckValidationLayerSupport(layers);
    }
    
    vk::InstanceCreateInfo instanceCI{.pApplicationInfo = appInfo};
    
    instanceCI.setPEnabledExtensionNames(extensions);
    instanceCI.setPEnabledLayerNames(layers);
    
    return instanceCI;
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
  
  void EngineVK::AddWindow(void * window)
  {
    //vk::SurfaceKHR surfaceHandle;
    //SDL_Vulkan_CreateSurface(static_cast<SDL_Window *>(window), *_vkInstance, (VkSurfaceKHR *)(&surfaceHandle));
    //vk::raii::SurfaceKHR raiiSurface(_vkInstance, surfaceHandle);
    
    //_deviceManagers[0].AddSurface(std::move(raiiSurface));
  }
}