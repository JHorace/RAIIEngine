// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_ENGINE_VK_FACTORY_HPP
#define RAIIENGINE_ENGINE_VK_FACTORY_HPP

#include <array>
#include "i_engine_factory.hpp"

namespace Forge
{
  class EngineVKFactory : public IEngineFactory
  {
  public:
    IEngine * CreateEngine() override;
    IEngine * CreateEngine(const EngineConfigInfo& configInfo) override;
    ~EngineVKFactory() override = default;
  };
}

#endif //RAIIENGINE_ENGINE_VK_FACTORY_HPP
