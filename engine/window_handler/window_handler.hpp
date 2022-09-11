// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifndef RAIIENGINE_WINDOW_HANDLER_HPP
#define RAIIENGINE_WINDOW_HANDLER_HPP

class GLFWwindow;

#ifdef _WIN32
typedef void * HWND;
#elif __linux__

#endif

namespace Forge
{
#ifdef _WIN32
  HWND MakeNativeWindow(GLFWwindow * window);
#elif __linux__

#endif

}

#endif //RAIIENGINE_WINDOW_HANDLER_HPP
