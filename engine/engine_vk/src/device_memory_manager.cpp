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
  const vk::MemoryPropertyFlags stagingProperties = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
  
  DeviceMemoryManager::DeviceMemoryManager(const vk::raii::Device & _vkDevice,
                                           const vk::PhysicalDeviceMemoryProperties & memoryProperties) : _VBO{_vkDevice,
                                                                                                               memoryProperties,
                                                                                                               VBOSIZE, VBOUsage, VBOProperties},
                                                                                                          _staging{_vkDevice, memoryProperties, VBOSIZE, stagingUsage}
  {
  
  }
}
