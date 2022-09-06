// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_DEBUG_HPP
#define RAIIENGINE_DEBUG_HPP

#include "p_includes.hpp"

namespace spdlog
{
  class logger;
}

namespace Forge
{

  inline constexpr std::array<const char *, 1> DEBUG_EXTENSIONS{ VK_EXT_DEBUG_UTILS_EXTENSION_NAME };
  inline constexpr std::array<const char *, 1> DEBUG_LAYERS{ "VK_LAYER_KHRONOS_validation" };
  inline constexpr vk::DebugUtilsMessageSeverityFlagsEXT MESSAGE_SEVERITY
  {
    vk::DebugUtilsMessageSeverityFlagBitsEXT::eError |
    vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
  };
  inline constexpr vk::DebugUtilsMessageTypeFlagsEXT MESSAGE_TYPE
  {
    vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
    vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
    vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance
  };

  class Logger
  {
  public:
    Logger(vk::raii::Instance const & instance);

    static vk::Bool32 debugCallback(
      VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
      VkDebugUtilsMessageTypeFlagsEXT messageType,
      const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData,
      void * pUserData);

    std::shared_ptr<spdlog::logger> _info;
    std::shared_ptr<spdlog::logger> _error;
  private:
    vk::raii::DebugUtilsMessengerEXT CreateDebugUtilsMessenger(vk::raii::Instance const & instance);
    vk::raii::DebugUtilsMessengerEXT _messenger;
  };
}


#endif //RAIIENGINE_DEBUG_HPP
