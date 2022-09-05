//
// Created by James on 9/4/2022.
//

#ifndef RAIIENGINE_DEBUG_HPP
#define RAIIENGINE_DEBUG_HPP

#include "p_includes.hpp"

namespace spdlog {
  class logger;
}

namespace Forge {
  namespace Debug {

    inline constexpr std::array<const char *, 1> DEBUG_EXTENSIONS = {VK_EXT_DEBUG_UTILS_EXTENSION_NAME};
    inline constexpr std::array<const char *, 1> DEBUG_LAYERS = {"VK_LAYER_KHRONOS_validation"};

    class Logger {
    public:
      Logger(vk::raii::Instance const &instance);

      static vk::Bool32 debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                      VkDebugUtilsMessageTypeFlagsEXT messageType,
                                      const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                      void *pUserData);

      std::shared_ptr<spdlog::logger> _info;
      std::shared_ptr<spdlog::logger> _error;
    private:
      vk::raii::DebugUtilsMessengerEXT _messenger;
    };
  }

}


#endif //RAIIENGINE_DEBUG_HPP
