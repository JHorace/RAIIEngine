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
  
  struct EngineConfigInfo
  {
    const char* _appName{"Default App"};
    const char* _engineName{"Default Engine"};
    unsigned _engineVersionMajor{1};
    unsigned _engineVersionMinor{0};
    unsigned _appVersionMajor{1};
    unsigned _appVersionMinor{0};
  };
  
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
