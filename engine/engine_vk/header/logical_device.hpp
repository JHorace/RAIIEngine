// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_LOGICAL_DEVICE_HPP
#define RAIIENGINE_LOGICAL_DEVICE_HPP

#include "p_includes.hpp"
#include "queue_manager.hpp"
#include "surface.hpp"
#include "renderer.hpp"
#include "command_dispatch.hpp"

namespace Forge
{
  
  class LogicalDevice
  {
  public:
    LogicalDevice(
      const vk::raii::PhysicalDevice & physDevice,
      vk::DeviceQueueCreateInfo deviceQueueCI,
      std::vector<const char *> extensions,
      std::vector<const char *> layers);
    
    void CreateSwapchainFromSurface(const Surface & surface);
    
    const vk::raii::Device & operator*() const;
  
    LogicalDevice(LogicalDevice && other) noexcept = default;
    LogicalDevice(const LogicalDevice &) = delete;
    LogicalDevice operator=(const LogicalDevice &) = delete;
  private:
    vk::DeviceCreateInfo CIBuilder(
      vk::DeviceQueueCreateInfo & deviceQueueCI,
      std::vector<const char *> & extensions,
      std::vector<const char *> & layers);
    
    vk::raii::Device _vkDevice;
    std::vector<Swapchain> _swapchains;
    uint32_t _presentQueueFamilyIndex;
    CommandDispatch _commandDispatch;
  };
}

#endif //RAIIENGINE_LOGICAL_DEVICE_HPP
