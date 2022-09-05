//
// Created by James on 8/31/2022.
//

#ifndef RAIIENGINE_DEVICE_WRAPPER_HPP
#define RAIIENGINE_DEVICE_WRAPPER_HPP

#include "p_includes.hpp"
#include "queue_manager.hpp"

namespace Forge {
  namespace Device {

    inline constexpr std::array<const char *, 2> DEFAULT_EXTENSIONS = {"VK_KHR_swapchain",
                                                                       "VK_KHR_dynamic_rendering"};


    /// Encapsulates relevant information about a physical device. Contains the handle for a corresponding
    /// logical device,
    /// and implements additional utilities for that logical device
    class DeviceWrapper {
    public:
      DeviceWrapper(const vk::raii::PhysicalDevice &physDevice,
                    std::vector<const char *> extensions,
                    std::vector<const char *> layers);

      DeviceWrapper(const DeviceWrapper &) = delete;

      DeviceWrapper operator=(const DeviceWrapper &) = delete;

      QueueManager _queueManager;
    private:
      vk::raii::Device CreateDeviceFromPhysicalDevice(vk::raii::PhysicalDevice const &physDevice,
                                                      std::vector<const char *> extensions = std::vector<const char *>{},
                                                      std::vector<const char *> layers = std::vector<const char *>{});
      vk::raii::Device _device;
    };
  }
}


#endif //RAIIENGINE_DEVICE_WRAPPER_HPP
