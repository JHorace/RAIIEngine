// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_I_ENGINE_HPP
#define RAIIENGINE_I_ENGINE_HPP

namespace Forge
{
  class IEngine
  {
  public:
    virtual ~IEngine()
    {
    };
    virtual void Render() = 0;
  private:
  };
}

#endif //RAIIENGINE_I_ENGINE_HPP
