// Created 2022
// James Sumihiro and Bryan Johnson
//


#ifndef RAIIENGINE_LOGICAL_DEVICE_HPP
#define RAIIENGINE_LOGICAL_DEVICE_HPP

#include "p_includes.hpp"
#include "queue_manager.hpp"

namespace Forge
{
  inline constexpr std::array DEVICE_EXTENSIONS
  {
    "VK_KHR_swapchain",
    "VK_KHR_dynamic_rendering"
  };
  
  class LogicalDevice
  {
  public:
    LogicalDevice(
      const vk::raii::PhysicalDevice & physDevice,
      vk::DeviceQueueCreateInfo deviceQueueCI,
      std::vector<const char *> extensions,
      std::vector<const char *> layers);
    
    const vk::raii::Device & operator*() const;
    
    LogicalDevice(const LogicalDevice &) = delete;
    LogicalDevice operator=(const LogicalDevice &) = delete;
  private:
    vk::raii::Device _vkDevice;
  };
}

#endif //RAIIENGINE_LOGICAL_DEVICE_HPP
