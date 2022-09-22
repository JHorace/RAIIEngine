// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_WINDOW_HANDLER_HPP
#define RAIIENGINE_WINDOW_HANDLER_HPP



class GLFWwindow;

#ifdef _WIN32
#include "windows.h"
typedef HWND WindowType;
typedef HINSTANCE MultiplexType;
#elif __linux__
#include "X11/Xlib.h"
typedef Window WindowType;
typedef Display* MultiplexType;
#endif

namespace Forge
{
  struct NativeWindow
  {
    NativeWindow(GLFWwindow * window);
    WindowType _window;
    MultiplexType _multiplex;
  };
  
}

#endif //RAIIENGINE_WINDOW_HANDLER_HPP
