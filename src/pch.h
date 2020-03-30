/**
 * @file    src/pch.h
 * @author  dragon-archer (dragon-archer@outlook.com)
 * @brief   The precompiled header
 * @version 0.0.1
 * 
 * @license This file is published under The MIT License
 *          See License in the root directory for details
 *          Copyright (c) 2020 dragon-archer
 */

#ifndef _2048_PCH_H
#define _2048_PCH_H 1

#ifdef _MSC_VER /* MSVC compatiblilty */
#pragma once
#endif /* _MSC_VER */

/**
 * @brief Detect OS
 */
#if defined(WINDOWS) || defined(WIN32) || defined(_WINDOWS) /* Windows system */
    #define OS_WINDOWS
    #define WINDOWS_LEAN_AND_MEAN /* Remove unused definations in `Windows.h` */
    #define NO_MINMAX /* Use C++ standard min/max, turn off Windows macros */
    #include <Windows.h>
#elif defined(linux) || defined(__linux__) /* Linux system */
    #define OS_LINUX
    #include <sys/types.h>
    #include <sys/ioctl.h>
    #include <unistd.h>
#else /* Unknown OS */
    #error "This program currently not support your operating system.\n" \
           "Please use Windows or Linux instead."
#endif

/**
 * @brief Include standard headers
 */
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <random>

#endif /* _2048_PCH_H */
