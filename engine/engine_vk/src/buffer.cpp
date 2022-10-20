// Created 2022
// James Sumihiro and Bryan Johnson
//
#include "buffer.hpp"
#include "vertex.hpp"
#include <optional>

namespace Forge
{
  vk::raii::Buffer CreateBuffer(const vk::raii::Device & device,
                                vk::DeviceSize size,
                                vk::BufferUsageFlags usageFlags)
  {
    vk::BufferCreateInfo createInfo{
      .size = size,
      .usage = usageFlags,
      .sharingMode = vk::SharingMode::eExclusive
    };
    
    return vk::raii::Buffer{device, createInfo};
  }
  
  std::optional<uint32_t> GetSuitableMemoryIndex(const vk::PhysicalDeviceMemoryProperties & memoryProperties,
                                                 uint32_t memoryTypeFlags,
                                                 vk::MemoryPropertyFlags memoryPropertyFlags)
  {
    for (int i = 0; i < 32; ++i)
      if (memoryTypeFlags & (1 << i))
        if ((memoryProperties.memoryTypes[i].propertyFlags & memoryPropertyFlags) == memoryPropertyFlags)
          return i;
    
    return {};
  }
  
  vk::raii::DeviceMemory CreateMemory(const vk::raii::Device & device,
                                      const vk::PhysicalDeviceMemoryProperties & memoryProperties,
                                      const vk::raii::Buffer & buffer,
                                      vk::MemoryPropertyFlags memoryPropertyFlags)
  {
    auto requirements = buffer.getMemoryRequirements();
    
    auto typeIndex = GetSuitableMemoryIndex(memoryProperties, requirements.memoryTypeBits, memoryPropertyFlags);
    
    if (!typeIndex.has_value())
      throw std::runtime_error("Could not find suitable memory for buffer.");
    
    vk::MemoryAllocateInfo allocateInfo{
      .allocationSize = requirements.size,
      .memoryTypeIndex = typeIndex.value()
    };
    
    return vk::raii::DeviceMemory{device, allocateInfo};
  }
  
  Buffer::Buffer(const vk::raii::Device & device,
                 const vk::PhysicalDeviceMemoryProperties & memoryProperties,
                 vk::DeviceSize size,
                 vk::BufferUsageFlags usageFlags,
                 vk::MemoryPropertyFlags memoryPropertyFlags)
    :
    _buffer{CreateBuffer(device, size, usageFlags)},
    _deviceMemory{CreateMemory(device, memoryProperties, _buffer, memoryPropertyFlags)},
    _size(size)
  {
    Bind();
  }
  
  void Buffer::CopyFromBuffer(const vk::raii::CommandBuffer & commandBuffer,
                              const vk::raii::Queue & queue,
                              const Buffer & otherBuffer,
                              vk::DeviceSize size)
  {
    if (size == 0)
    {
      size = _size;
    }
    
    vk::CommandBufferBeginInfo beginInfo{};
    vk::BufferCopy copyRegion{
      .size = size
    };
    
    commandBuffer.begin(beginInfo);
    commandBuffer.copyBuffer(**otherBuffer, *_buffer, copyRegion);
    commandBuffer.end();
    
    vk::SubmitInfo submitInfo{
      .commandBufferCount = 1,
      .pCommandBuffers = &*commandBuffer
    };
    
    queue.submit(submitInfo);
    queue.waitIdle();
  }
  
  void Buffer::Bind()
  {
    _buffer.bindMemory(*_deviceMemory, 0);
  }
  
  vk::raii::Buffer & Buffer::operator*()
  {
    return _buffer;
  }
  
  const vk::raii::Buffer & Buffer::operator*() const
  {
    return _buffer;
  }
  
  StagingBuffer::StagingBuffer(const vk::raii::Device & device,
                               const vk::PhysicalDeviceMemoryProperties & memoryProperties,
                               vk::DeviceSize size,
                               vk::BufferUsageFlags usageFlags)
    :
    Buffer(device, memoryProperties, size, usageFlags,
           vk::MemoryPropertyFlagBits::eHostVisible
           | vk::MemoryPropertyFlagBits::eHostCoherent)
  {
    MapMemory(unitTriangle.data(), unitTriangle.size() * sizeof(Vertex));
  }
  
  void StagingBuffer::MapMemory(const void * srcData,
                                size_t size)
  {
    void * dstData = _deviceMemory.mapMemory(0, size);
    memcpy(dstData, srcData, size);
    _deviceMemory.unmapMemory();
  }
}
