// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_BUFFER_HPP
#define RAIIENGINE_BUFFER_HPP

#include "p_includes.hpp"

namespace Forge
{
  class Buffer
  {
  public:
    Buffer(const vk::raii::Device & device,
           const vk::PhysicalDeviceMemoryProperties & memoryProperties,
           vk::DeviceSize size,
           vk::BufferUsageFlags usageFlags,
           vk::MemoryPropertyFlags memoryPropertyFlags);
    
    
    void CopyFromBuffer(const vk::raii::CommandBuffer & commandBuffer,
                        const Buffer & otherBuffer,
                        vk::DeviceSize size);
    void Bind();
    
    vk::raii::Buffer & operator*();
    const vk::raii::Buffer & operator*() const;
  protected:
    vk::raii::Buffer _buffer;
    vk::raii::DeviceMemory _deviceMemory;
    vk::DeviceSize _size;
  };
  
  class StagingBuffer : public Buffer
  {
  public:
    StagingBuffer(const vk::raii::Device & device,
                  const vk::PhysicalDeviceMemoryProperties & memoryProperties,
                  vk::DeviceSize size,
                  vk::BufferUsageFlags usageFlags);
    
    void MapMemory(void * srcData,
                   size_t size);
  protected:
  };
  
  
  class DeviceBuffer : public Buffer
  {
  public:
    using Buffer::Buffer;
  private:
  
  };
}

#endif //RAIIENGINE_BUFFER_HPP
