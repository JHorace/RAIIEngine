// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_LOGICAL_DEVICE_HPP
#define RAIIENGINE_LOGICAL_DEVICE_HPP

#include "p_includes.hpp"
#include "queue_manager.hpp"
#include "surface.hpp"
#include "swapchain.hpp"
#include "command_dispatch.hpp"
#include "pipeline.hpp"
#include "shader.hpp"
#include "device_memory_manager.hpp"

namespace Forge
{
  typedef unsigned int WindowID;
  
  class LogicalDevice
  {
  public:
    LogicalDevice(
      const vk::raii::PhysicalDevice & physDevice,
      vk::DeviceQueueCreateInfo deviceQueueCI,
      std::vector<const char *> extensions,
      std::vector<const char *> layers);
    
    void Update(const Surface & surface);
    
    void CreateSwapchainFromSurface(const Surface & surface);
    
    void CreateDefaultPipeline();
    
    void CreateDefaultShaders();
  
    CommandDispatch & GetDispatch();
    const Swapchain & GetSwapchain(WindowID windowID) const;
    
    const vk::raii::Device & operator*() const;
  
    LogicalDevice(LogicalDevice && other) noexcept = default;
    LogicalDevice(const LogicalDevice &) = delete;
    LogicalDevice operator=(const LogicalDevice &) = delete;
  private:
    void Draw(const Surface & surface);
    void PresentToQueue();
    
    vk::DeviceCreateInfo CIBuilder(
      vk::DeviceQueueCreateInfo & deviceQueueCI,
      std::vector<const char *> & extensions,
      std::vector<const char *> & layers);
  
    
    vk::PhysicalDeviceDynamicRenderingFeatures _dynamicRenderingFeatures;

    vk::raii::Device _vkDevice;
  
    uint32_t _presentQueueFamilyIndex;
    CommandDispatch _commandDispatch;
    DeviceMemoryManager _deviceMemoryManager;
    
    vk::raii::Semaphore _imageAvailableSemaphore;
    vk::raii::Semaphore _presentReadySemaphore;
    vk::raii::Fence _drawReadyFence;
  
    std::vector<Swapchain> _swapchains;
    std::vector<Shader> _shaders;
    std::vector<Pipeline> _pipelines;
  };
}

#endif //RAIIENGINE_LOGICAL_DEVICE_HPP
