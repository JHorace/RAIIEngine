// Created 2022
// James Sumihiro and Bryan Johnson
//

#include "logical_device.hpp"

namespace Forge
{
  
  LogicalDevice::LogicalDevice(
    const vk::raii::PhysicalDevice & physDevice,
    vk::DeviceQueueCreateInfo deviceQueueCI,
    std::vector<const char *> extensions,
    std::vector<const char *> layers)
    :
    _vkDevice{physDevice, CIBuilder(deviceQueueCI, extensions, layers)},
    _presentQueueFamilyIndex{deviceQueueCI.queueFamilyIndex},
    _commandDispatch{_vkDevice, 3, deviceQueueCI.queueFamilyIndex}
  {
  
  }
  
  const vk::raii::Device & LogicalDevice::operator*() const
  {
    return _vkDevice;
  }
  
  vk::DeviceCreateInfo LogicalDevice::CIBuilder(
    vk::DeviceQueueCreateInfo & deviceQueueCI,
    std::vector<const char *> & extensions,
    std::vector<const char *> & layers)
  {
    vk::DeviceCreateInfo deviceCI{};
    deviceCI.setQueueCreateInfos(deviceQueueCI);
    deviceCI.setPEnabledExtensionNames(extensions);
    deviceCI.setPEnabledLayerNames(layers);
    
    return deviceCI;
  }
  
  void LogicalDevice::CreateSwapchainFromSurface(const Surface & surface)
  {
    _swapchains.emplace_back(Swapchain{_vkDevice, surface});
    
    CreateDefaultPipeline(); // TODO: Move this somewhere else.
    CreateDefaultShaders(); // TODO: Move this somewhere else.
  }
  
  CommandDispatch & LogicalDevice::GetDispatch()
  {
    return _commandDispatch;
  }
  
  const Swapchain & LogicalDevice::GetSwapchain(WindowID windowID) const
  {
    return _swapchains[windowID];
  }
  
  void LogicalDevice::CreateDefaultPipeline()
  {
    _pipelines.emplace_back(Pipeline(_vkDevice));
  }
  
  void LogicalDevice::CreateDefaultShaders()
  {
    auto vertBytes = Shader::CompileSPV("assets/shaders/simple.vert", Shader::Stage::vertex);
    _shaders.emplace_back(Shader(_vkDevice, vertBytes, Shader::Stage::vertex));
    auto fragBytes = Shader::CompileSPV("assets/shaders/simple.frag", Shader::Stage::fragment);
    _shaders.emplace_back(Shader(_vkDevice, fragBytes, Shader::Stage::fragment));
  }
}

