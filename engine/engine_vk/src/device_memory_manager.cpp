// Created 2022
// James Sumihiro and Bryan Johnson
//
#include "device_memory_manager.hpp"

struct Vertex
{

};


namespace Forge
{
  const uint64_t VBOSIZE = sizeof(Vertex) * MAX_VERTICES;
  
  const vk::BufferUsageFlags VBOUsage = vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer;
  const vk::BufferUsageFlags stagingUsage = vk::BufferUsageFlagBits::eTransferSrc;
  
  const vk::MemoryPropertyFlags VBOProperties = vk::MemoryPropertyFlagBits::eDeviceLocal;
  const vk::MemoryPropertyFlags stagingProperties =
    vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
  
  DeviceMemoryManager::DeviceMemoryManager(const vk::raii::Device & device,
                                           const vk::PhysicalDeviceMemoryProperties & memoryProperties)
    :
    _VBO{device, memoryProperties, VBOSIZE, VBOUsage, VBOProperties},
    _staging{device, memoryProperties, VBOSIZE, stagingUsage}
  {
  
  }
  
  void DeviceMemoryManager::StageVBO(const vk::raii::CommandBuffer & commandBuffer,
                                     const vk::raii::Queue & queue)
  {
    _VBO.CopyFromBuffer(commandBuffer, queue, _staging);
  }
  
  const Buffer & DeviceMemoryManager::GetVBO() const
  {
    return _VBO;
  }
}
