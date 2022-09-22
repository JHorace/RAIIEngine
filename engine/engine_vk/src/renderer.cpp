// Created 2022
// James Sumihiro and Bryan Johnson
//

#include "renderer.hpp"

namespace Forge
{
  
  Renderer::Renderer()
  {
    _renderingInfo = vk::RenderingInfo{
      .renderArea = vk::Rect2D(),
      .layerCount = 1,
      .colorAttachmentCount = 1,
      .pColorAttachments = &_colorAttachInfo,
      .pDepthAttachment = nullptr,
      .pStencilAttachment = nullptr
    };
    _colorAttachInfo = vk::RenderingAttachmentInfo{
      .imageLayout = vk::ImageLayout::eAttachmentOptimal,
      .loadOp = vk::AttachmentLoadOp::eClear,
      .storeOp = vk::AttachmentStoreOp::eStore
    };
  }
  
  void Renderer::Draw(LogicalDevice & device)
  {
    auto commandBuffer = device.GetCommandBuffer();
    
    commandBuffer.beginRendering(_renderingInfo);
    
    vk::PipelineRenderingCreateInfo{
      .colorAttachmentCount = 1,
      .pColorAttachmentFormats =
    };
    
    commandBuffer.endRendering();
  }
}
