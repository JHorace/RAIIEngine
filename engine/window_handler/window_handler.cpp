// Created 2022
// James Sumihiro and Bryan Johnson
//
#include "window_handler.hpp"

#define GLFW_NATIVE_INCLUDE_NONE

#ifdef _WIN32
#include "winuser.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "libloaderapi.h"
#elif __linux__
#define GLFW_EXPOSE_NATIVE_X11
#endif

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

namespace Forge
{
#ifdef _WIN32
  NativeWindow::NativeWindow(GLFWwindow * window) :
    _window(glfwGetWin32Window(window)),
    _multiplex(GetModuleHandle(NULL))
  {};
#elif __linux__
  NativeWindow::NativeWindow(GLFWwindow * window) :
    _window(glfwGetX11Window(window)),
    _multiplex(glfwGetX11Display()){}

#endif
}