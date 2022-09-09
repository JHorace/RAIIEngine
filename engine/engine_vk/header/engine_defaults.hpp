// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_ENGINE_DEFAULTS_HPP
#define RAIIENGINE_ENGINE_DEFAULTS_HPP

#include <array>

namespace Forge
{
  
  inline constexpr std::array DEFAULT_DEVICE_EXTENSIONS
    {
      "VK_KHR_swapchain",
      "VK_KHR_dynamic_rendering"
    };
  inline constexpr std::array DEBUG_EXTENSIONS
    {
      "VK_EXT_debug_utils"
    };
  inline constexpr std::array DEBUG_LAYERS
    {
      "VK_LAYER_KHRONOS_validation"
    };
}

#endif //RAIIENGINE_ENGINE_DEFAULTS_HPP
