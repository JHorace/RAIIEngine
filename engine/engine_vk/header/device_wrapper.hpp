// Created 2022
// James Sumihiro and Bryan Johnson
//


#ifndef RAIIENGINE_DEVICE_WRAPPER_HPP
#define RAIIENGINE_DEVICE_WRAPPER_HPP

#include "p_includes.hpp"
#include "queue_manager.hpp"

namespace Forge
{
  inline constexpr std::array<const char *, 2> DEFAULT_EXTENSIONS
  {
    "VK_KHR_swapchain",
    "VK_KHR_dynamic_rendering"
  };

  /// Encapsulates relevant information about a physical device. Contains the handle for a corresponding
  /// logical device, and implements additional utilities for that logical device
  class Device
  {
  public:
    Device(
      const vk::raii::PhysicalDevice & physDevice,
      std::vector<const char *> extensions,
      std::vector<const char *> layers);

    Device(const Device &) = delete;

    Device operator=(const Device &) = delete;

    QueueManager _queueManager;
    vk::raii::PhysicalDevice _vkPhysicalDevice;
    vk::raii::Device _vkDevice;
  private:

  };
}

#endif //RAIIENGINE_DEVICE_WRAPPER_HPP
