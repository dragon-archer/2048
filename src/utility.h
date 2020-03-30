/**
 * @file    src/utility.h
 * @author  dragon-archer (dragon-archer@outlook.com)
 * @brief   Utility functions definations
 * @version 0.0.1
 * 
 * @license This file is published under The MIT License
 *          See License in the root directory for details
 *          Copyright (c) 2020 dragon-archer
 */

#ifndef _2048_UTILITY_H
#define _2048_UTILITY_H 1

#ifdef _MSC_VER /* MSVC compatiblilty */
#pragma once
#endif /* _MSC_VER */

#include <pch.h>

/**
 * @brief Put the cursor to (x, y)
 * 
 * @param x row number, begin at 0
 * @param y column nu,ber, begin at 0
 */
void gotoxy(int x, int y);

/**
 * @brief Clear screen
 */
void cls();

#endif /* _2048_UTILITY_H */
