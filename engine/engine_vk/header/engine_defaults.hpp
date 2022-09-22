// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_ENGINE_DEFAULTS_HPP
#define RAIIENGINE_ENGINE_DEFAULTS_HPP

#include <array>

namespace Forge
{
  inline constexpr std::array INSTANCE_EXTENSIONS
    {
      "VK_KHR_surface"
#ifdef _WIN32
      ,"VK_KHR_win32_surface"
#elif __linux__
    ,"VK_KHR_xlib_surface"
#endif
    };
  inline constexpr std::array<const char *, 0> INSTANCE_LAYERS
    {
    
    };
  
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
