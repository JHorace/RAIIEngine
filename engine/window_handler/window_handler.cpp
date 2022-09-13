// Created 2022
// James Sumihiro and Bryan Johnson
//
#include "window_handler.hpp"
#include "winuser.h"
#define GLFW_NATIVE_INCLUDE_NONE

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#elif __linux__
#define GLFW_EXPOSE_NATIVE_X11
#endif

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include "libloaderapi.h"
namespace Forge
{
#ifdef _WIN32
  NativeWindow::NativeWindow(GLFWwindow * window) :
    _window(glfwGetWin32Window(window)),
    _multiplex(GetModuleHandleA(NULL))
  {};
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