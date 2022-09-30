// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_I_ENGINE_HPP
#define RAIIENGINE_I_ENGINE_HPP

#include "window_handler.hpp"

#ifdef NDEBUG
inline constexpr bool DEBUG_LOGGING = false;
#else
inline constexpr bool DEBUG_LOGGING = true;
#endif // NDEBUG

namespace Forge
{
  typedef unsigned int WindowID;
  
  class IEngine
  {
  public:
    virtual ~IEngine()
    {
    };
    virtual void Render() = 0;
    virtual void AddWindow(Forge::NativeWindow window) = 0;
  private:
  };
}

#endif //RAIIENGINE_I_ENGINE_HPP
