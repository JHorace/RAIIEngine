// Created 2022
// James Sumihiro and Bryan Johnson
//

#ifdef _WIN32
#elif __linux__
#define GLFW_EXPOSE_NATIVE_X11
#include "window_handler.hpp"
#include "X11/Xlib.h"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#endif

namespace Forge
{
#ifdef _WIN32
  HWND MakeNativeWindow(GLFWwindow * window)
  {
    return nullptr;
  }
#elif __linux__
  Window GetNativeWindow(GLFWwindow * window)
  {
    return glfwGetX11Window(window);
  }
  
  Display* GetNativeDisplay()
  {
    return glfwGetX11Display();
  }

#endif


}