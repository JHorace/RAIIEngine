// Created 2022
// James Sumihiro
//

#ifndef RAIIENGINE_P_INCLUDES_HPP
#define RAIIENGINE_P_INCLUDES_HPP

#define VULKAN_HPP_NO_CONSTRUCTORS
#define VULKAN_HPP_TYPESAFE_CONVERSION

#ifdef _WIN32
#include "windows.h"
#define VK_USE_PLATFORM_WIN32_KHR
#elif __linux__
#include "X11/Xlib.h"
#define VK_USE_PLATFORM_XLIB_KHR
#endif


#include <memory>
#include <vulkan/vulkan_raii.hpp>



#endif //RAIIENGINE_P_INCLUDES_HPP
