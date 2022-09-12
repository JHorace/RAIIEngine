// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_WINDOW_HANDLER_HPP
#define RAIIENGINE_WINDOW_HANDLER_HPP



class GLFWwindow;

#ifdef _WIN32
typedef void * HWND;
#elif __linux__
#include "X11/Xlib.h"
#endif

namespace Forge
{
#ifdef _WIN32
  HWND MakeNativeWindow(GLFWwindow * window);
#elif __linux__
  Window GetNativeWindow(GLFWwindow * window);
  Display* GetNativeDisplay();
#endif

}

#endif //RAIIENGINE_WINDOW_HANDLER_HPP
