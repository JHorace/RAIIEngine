// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_I_ENGINE_FACTORY_HPP
#define RAIIENGINE_I_ENGINE_FACTORY_HPP

#include "i_engine.hpp"

namespace Forge
{

  class IEngineFactory
  {
  public:
    virtual ~IEngineFactory()
    {
    };
    virtual IEngine * CreateEngine() = 0;
    virtual IEngine * CreateEngine(const EngineConfigInfo& configInfo) = 0;
  };
}

#endif //RAIIENGINE_I_ENGINE_FACTORY_HPP
