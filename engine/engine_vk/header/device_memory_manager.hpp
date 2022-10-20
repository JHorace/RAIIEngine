// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_DEVICE_MEMORY_MANAGER_HPP
#define RAIIENGINE_DEVICE_MEMORY_MANAGER_HPP

#include "buffer.hpp"
#include "command_dispatch.hpp"

namespace Forge
{
  
  inline constexpr uint32_t MAX_VERTICES = 1000;
  
  class DeviceMemoryManager
  {
  public:
    DeviceMemoryManager(const vk::raii::Device & device,
                        const vk::PhysicalDeviceMemoryProperties & memoryProperties);
    
    const Buffer & GetVBO() const;
    void StageVBO(const vk::raii::CommandBuffer & commandBuffer,
                  const vk::raii::Queue & queue);
  private:
    StagingBuffer _staging;
    Buffer _VBO;
  };
}

#endif //RAIIENGINE_DEVICE_MEMORY_MANAGER_HPP
