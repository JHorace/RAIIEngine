//
// Created by James on 8/27/2022.
//

#ifndef RAIIENGINE_ENGINE_VK_HPP
#define RAIIENGINE_ENGINE_VK_HPP

#include "i_engine.hpp"
#include "p_includes.hpp"

namespace Forge {

  class EngineVK : public IEngine {
  public:
    EngineVK();

    void Render() override;

  private:
    vk::raii::Context _context;
    vk::raii::Instance _instance;
    vk::raii::PhysicalDevice _physDevice;

    //   vk::raii::Device _device;

    /*
    vk::raii::PhysicalDevice _physicalDevice;
    vk::raii::Device _device;
    vk::raii::DebugUtilsMessengerEXT _messenger;
     */

  };
}


#endif //RAIIENGINE_ENGINE_VK_HPP

