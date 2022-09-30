// Created 2022
// James Sumihiro and Bryan Johnson
//

#include "renderer.hpp"

namespace Forge
{
  
  Renderer::Renderer()
  {
  }
  
  
  
  void Renderer::Draw(LogicalDevice & device, Pipeline & pipeline, WindowID windowID)
  {
    auto & commandBuffer = device.GetDispatch().GetCommandBuffer();
    auto & currentImage = device.GetSwapchain(windowID).GetCurrentImage();
    
    commandBuffer.beginRendering(pipeline._renderingInfo);
    
    vk::PipelineRenderingCreateInfo{
      .colorAttachmentCount = 1,
      .pColorAttachmentFormats = &currentImage.format
    };
    
    commandBuffer.endRendering();
  }
}
