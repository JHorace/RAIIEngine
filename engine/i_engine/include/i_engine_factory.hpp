// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_I_ENGINE_FACTORY_HPP
#define RAIIENGINE_I_ENGINE_FACTORY_HPP

namespace Forge
{
  class IEngine;

  class IEngineFactory
  {
  public:
    virtual ~IEngineFactory()
    {
    };
    virtual IEngine * CreateEngine() = 0;
  };
}

#endif //RAIIENGINE_I_ENGINE_FACTORY_HPP
