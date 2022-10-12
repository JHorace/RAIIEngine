// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_PIPELINE_HPP
#define RAIIENGINE_PIPELINE_HPP

#include <array>
#include "p_includes.hpp"
#include "shader.hpp"
#include <unordered_map>

namespace Forge
{
  class Pipeline
  {
  public:
    explicit Pipeline(const vk::raii::Device & device,
                      const std::vector<vk::PipelineShaderStageCreateInfo> & shaderStageCIs);
    
    const vk::raii::Pipeline & operator*();
    
    vk::PipelineLayoutCreateInfo PipelineLayoutCIBuilder();
    vk::GraphicsPipelineCreateInfo PipelineCIBuilder(
      const std::vector<vk::PipelineShaderStageCreateInfo> & shaderStageCIs);
    
    vk::RenderingInfo _renderingInfo;
    vk::RenderingAttachmentInfo _colorAttachInfo;
    vk::RenderingAttachmentInfo _depthAttachInfo;
    vk::RenderingAttachmentInfo _stencilAttachInfo;
  private:
    vk::raii::PipelineLayout _pipelineLayout;
    vk::raii::Pipeline _pipeline;
  };
  
  // TODO: Move this to another file and/or refactor.
  namespace DefaultPipeline
  {
    inline constexpr std::array vertexAttributes{
      vk::VertexInputAttributeDescription{
        .location = 0,
        .binding = 0,
        .format = vk::Format::eR32G32B32Sfloat,
        .offset = 0
      },
      vk::VertexInputAttributeDescription{
        .location = 1,
        .binding = 0,
        .format = vk::Format::eR32G32B32Sfloat,
        .offset = 12 // Size of previous vertex attribute
      }
    };
    
    inline constexpr std::array vertexBindings{
      vk::VertexInputBindingDescription{
        .binding = 0,
        .stride = 24, // Size of a vertex.
        .inputRate = vk::VertexInputRate::eVertex
      }
    };
    
    inline constexpr vk::PipelineVertexInputStateCreateInfo vertexInputCI{
      .vertexBindingDescriptionCount = (uint32_t) vertexBindings.size(),
      .pVertexBindingDescriptions = vertexBindings.data(),
      .vertexAttributeDescriptionCount = (uint32_t) vertexAttributes.size(),
      .pVertexAttributeDescriptions = vertexAttributes.data()
    };
    
    inline constexpr vk::PipelineVertexInputStateCreateInfo emptyVertexInputCI{
      .vertexBindingDescriptionCount = 0,
      .pVertexBindingDescriptions = nullptr,
      .vertexAttributeDescriptionCount = 0,
      .pVertexAttributeDescriptions = nullptr
    };
    
    inline constexpr vk::PipelineInputAssemblyStateCreateInfo inputAssemblyCI{
      .topology = vk::PrimitiveTopology::eTriangleList,
      .primitiveRestartEnable = false
    };
    
    inline constexpr vk::PipelineRasterizationStateCreateInfo rasterizationCI{
      .depthClampEnable = false,
      .rasterizerDiscardEnable = false,
      .polygonMode = vk::PolygonMode::eFill,
      .cullMode = vk::CullModeFlagBits::eNone, // TODO: revert to eBack
      .frontFace = vk::FrontFace::eCounterClockwise,
      .depthBiasEnable = false,
      .lineWidth = 1
    };
    
    inline constexpr vk::PipelineMultisampleStateCreateInfo multisampleCI{
      .rasterizationSamples = vk::SampleCountFlagBits::e1,
      .sampleShadingEnable = false
    };
    
    inline constexpr vk::PipelineDepthStencilStateCreateInfo depthStencilCI{
      .depthTestEnable = true,
      .depthWriteEnable = true,
      .depthCompareOp = vk::CompareOp::eLess,
      .depthBoundsTestEnable = false,
      .stencilTestEnable = false,
      .front = vk::StencilOpState{
        .failOp = vk::StencilOp::eKeep,
        .passOp = vk::StencilOp::eKeep,
        .depthFailOp = vk::StencilOp::eKeep,
        .compareOp = vk::CompareOp::eAlways
      },
      .back = vk::StencilOpState{
        .failOp = vk::StencilOp::eKeep,
        .passOp = vk::StencilOp::eKeep,
        .depthFailOp = vk::StencilOp::eKeep,
        .compareOp = vk::CompareOp::eAlways
      }
    };
    
    inline constexpr vk::PipelineColorBlendAttachmentState colorBlendAttachment{
      .blendEnable = false,
      .srcColorBlendFactor = vk::BlendFactor::eZero,
      .dstColorBlendFactor = vk::BlendFactor::eZero,
      .colorBlendOp = vk::BlendOp::eAdd,
      .srcAlphaBlendFactor = vk::BlendFactor::eZero,
      .dstAlphaBlendFactor = vk::BlendFactor::eZero,
      .alphaBlendOp = vk::BlendOp::eAdd,
      .colorWriteMask = vk::ColorComponentFlagBits::eR
                        | vk::ColorComponentFlagBits::eB
                        | vk::ColorComponentFlagBits::eG
    };
    
    inline constexpr vk::PipelineViewportStateCreateInfo pipelineStateCI{
      .viewportCount = 1,
      .pViewports = nullptr,
      .scissorCount = 1,
      .pScissors = nullptr
    };
    
    inline constexpr vk::PipelineColorBlendStateCreateInfo colorBlendCI{
      .logicOpEnable = false,
      .logicOp = vk::LogicOp::eCopy,
      .attachmentCount = 1,
      .pAttachments = &colorBlendAttachment,
      .blendConstants = {}
    };
    
    inline constexpr std::array dynamicStates{
      vk::DynamicState::eViewport,
      vk::DynamicState::eScissor
    };
    
    inline constexpr vk::PipelineDynamicStateCreateInfo dynamicStateCI{
      .dynamicStateCount = (uint32_t) dynamicStates.size(),
      .pDynamicStates = dynamicStates.data()
    };
  }
}

#endif //RAIIENGINE_PIPELINE_HPP
