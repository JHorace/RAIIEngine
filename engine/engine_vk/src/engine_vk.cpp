// Created 2022
// James Sumihiro and Bryan Johnson
//

#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1

#include <iostream>

#include "debug.hpp"
#include "engine_vk.hpp"

VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

namespace Forge
{
  
  bool CheckValidationLayerSupport(std::vector<const char *> const & validationLayers);
  
  void EnableDebugValidation(
    std::vector<const char *> & extensions,
    std::vector<const char *> & layers
  );
  
  vk::raii::Instance CreateInstance(
    vk::raii::Context const & context,
    std::vector<const char *> instanceLayers,
    std::vector<const char *> instanceExtensions);
  
  vk::raii::Device CreateDevice(
    vk::raii::PhysicalDevice const & physDevice,
    std::vector<const char *> deviceExtensions,
    std::vector<const char *> deviceLayers);
  
  uint32_t FindQueueFamily(vk::raii::PhysicalDevice const & physDevice);
  
  vk::raii::Context CreateContext();
  
  // End forward declarations
  
  
  EngineVK::EngineVK(std::vector<const char *> extensions,
                     std::vector<const char *> layers)
    :
    _vkContext{},
    _vkInstance{CreateInstance(_vkContext, extensions, layers)},
    _deviceManager{_vkInstance}
  {
    std::cout << "NoCopy member initialization successful" << std::endl;
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
  
  bool CheckValidationLayerSupport(const vk::raii::Context & context, std::vector<const char *> const & validationLayers)
  {
    auto availableInstanceLayers = context.enumerateInstanceLayerProperties();
    
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
  
  void EnableDebugValidation(std::vector<const char *> & extensions,
                             std::vector<const char *> & layers)
  {
    extensions.insert(extensions.end(), DEBUG_EXTENSIONS.begin(), DEBUG_EXTENSIONS.end());
    layers.insert(layers.end(), DEBUG_LAYERS.begin(), DEBUG_LAYERS.end());
  }
  
  vk::raii::Instance CreateInstance(
    vk::raii::Context const & context,
    std::vector<const char *> extensions,
    std::vector<const char *> layers)
  {
    
    if (DEBUG_LOGGING)
    {
      EnableDebugValidation(extensions, layers);
      CheckValidationLayerSupport(context, layers);
    }
    
    vk::ApplicationInfo appInfo
      {
        .pApplicationName = "test",
        .applicationVersion = 1,
        .pEngineName = "Forge",
        .engineVersion = 1,
        .apiVersion = VK_API_VERSION_1_3,
      };
    
    vk::InstanceCreateInfo instanceCI
      {
        .pApplicationInfo = &appInfo
      };
    instanceCI.setPEnabledExtensionNames(extensions);
    instanceCI.setPEnabledLayerNames(layers);
    
    return {vk::raii::Instance(context, instanceCI)};
    
  }
  
  
  vk::raii::Device CreateDevice(vk::raii::PhysicalDevice const & physDevice,
                                std::vector<const char *> deviceExtensions,
                                std::vector<const char *> deviceLayers)
  {
    return vk::raii::Device(nullptr);
  }
  
  uint32_t FindQueueFamily(vk::raii::PhysicalDevice const & physDevice)
  {
    auto queueFamilyProperties = physDevice.getQueueFamilyProperties();
    
    for (uint32_t i = 0; i < queueFamilyProperties.size(); ++i)
      if (queueFamilyProperties[i].queueFlags & (vk::QueueFlagBits::eGraphics | vk::QueueFlagBits::eCompute))
        return i;
    
    return 0;
  }
  
}