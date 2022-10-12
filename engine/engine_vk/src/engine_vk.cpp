// Created 2022
// James Sumihiro and Bryan Johnson
//

#include <iostream>
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
  /*
  EngineVK::EngineVK(std::vector<const char *> extensions,
                     std::vector<const char *> layers)
    :
    _vkContext{},
    _vkInstance{_vkContext, CIBuilder(&APP_INFO, extensions, layers)},
    _logger{_vkInstance}
  {
    // Create a DeviceManager for each physical device.
    vk::raii::PhysicalDevices physDevices{_vkInstance};
    for (auto & physicalDevice: physDevices)
      _deviceManagers.emplace_back(DeviceManager(physicalDevice));
    
    
    const std::vector<const char *> device_extensions{DEFAULT_DEVICE_EXTENSIONS.begin(),
                                                      DEFAULT_DEVICE_EXTENSIONS.end()};
    _deviceManagers[0].AddLogicalDevice(device_extensions, layers);
  }
  */
  void EngineVK::Update()
  {
    for (auto & deviceManager : _deviceManagers)
    {
      deviceManager.Update();
    }
  }
  
 /*
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
  */
  
  bool EngineVK::CheckValidationLayerSupport(const vk::raii::Context & context, std::vector<const char *> const & validationLayers)
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
  
  void EngineVK::AddWindow(Forge::NativeWindow window)
  {

#ifdef _WIN32
    vk::Win32SurfaceCreateInfoKHR surfaceCI{
      .hinstance = window._multiplex,
      .hwnd = window._window
    };
    
    _deviceManagers[0].AddSurface(_vkInstance.createWin32SurfaceKHR(surfaceCI));
#elif __linux__
    vk::XlibSurfaceCreateInfoKHR surfaceCI{
      .dpy = window._multiplex,
      .window = window._window
    };
    _deviceManagers[0].AddSurface(_vkInstance.createXlibSurfaceKHR(surfaceCI));
#endif
    
  }
  
  EngineVK::EngineVK(const EngineConfigInfo & configInfo,
                     std::vector<const char *> extensions,
                     std::vector<const char *> layers)
    :
    _vkContext{},
    _vkInstance{CreateInstance(_vkContext, configInfo, extensions, layers)},
    _logger{_vkInstance}
  {
    // Create a DeviceManager for each physical device.
    vk::raii::PhysicalDevices physDevices{_vkInstance};
    for (auto & physicalDevice: physDevices)
      _deviceManagers.emplace_back(DeviceManager(physicalDevice));
    
    
    const std::vector<const char *> device_extensions{DEFAULT_DEVICE_EXTENSIONS.begin(),
                                                      DEFAULT_DEVICE_EXTENSIONS.end()};
    _deviceManagers[0].AddLogicalDevice(device_extensions, layers);
  }
  
  vk::raii::Instance EngineVK::CreateInstance(const vk::raii::Context & context,
                                              const EngineConfigInfo & configInfo,
                                              std::vector<const char *> extensions,
                                              std::vector<const char *> layers)
  {
    if (DEBUG_LOGGING)
    {
      // Add debug layers and extensions
      layers.insert(layers.end(), DEBUG_LAYERS.begin(), DEBUG_LAYERS.end());
      extensions.insert(extensions.end(), DEBUG_EXTENSIONS.begin(), DEBUG_EXTENSIONS.end());
      
      CheckValidationLayerSupport(context, layers);
    }
    
    vk::ApplicationInfo appInfo = AppInfoBuilder(configInfo);
    
    vk::InstanceCreateInfo instanceCI{.pApplicationInfo = &appInfo};
    
    instanceCI.setPEnabledExtensionNames(extensions);
    instanceCI.setPEnabledLayerNames(layers);
    
    return vk::raii::Instance{context, instanceCI};
    
  }
  
  vk::ApplicationInfo EngineVK::AppInfoBuilder(const EngineConfigInfo & configInfo)
  {
    return vk::ApplicationInfo{
      .pApplicationName = configInfo._appName,
      .applicationVersion = VK_MAKE_VERSION(configInfo._appVersionMajor, configInfo._appVersionMinor, 0),
      .pEngineName = configInfo._engineName,
      .engineVersion = VK_MAKE_VERSION(configInfo._engineVersionMajor, configInfo._engineVersionMinor, 0),
      .apiVersion = VK_API_VERSION_1_3,
    };
  }
  
}
