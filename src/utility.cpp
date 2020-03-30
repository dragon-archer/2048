/**
 * @file    src/utility.cpp
 * @author  dragon-archer (dragon-archer@outlook.com)
 * @brief   Utility functions
 * @version 0.0.1
 * 
 * @license This file is published under The MIT License
 *          See License in the root directory for details
 *          Copyright (c) 2020 dragon-archer
 */

#include <pch.h>
#include <utility.h>

/**
 * @brief Put the cursor to (x, y)
 * 
 * @param x row number, begin at 0
 * @param y column number, begin at 0
 */
void gotoxy(int x, int y)
{
#if defined(OS_WINDOWS)
	HANDLE hStdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	/**
	 * @note: Windows use COORD::X as column and COORD::Y as row,
	 *        and use SHORT (aka short) as type,
	 *        so we need to swap it and turn to SHORT.
	 */
	COORD coord {(SHORT)y, (SHORT)x};
	::SetConsoleCursorPosition(hStdOut, coord);
#elif defined(OS_LINUX)
	cout << "\e[" << x + 1 << ';' << y + 1 << 'H';
#endif
}

/**
 * @brief Clear screen
 */
void cls()
{
#if defined(OS_WINDOWS)
	system("cls");
#elif defined(OS_LINUX)
	system("clear");
#endif
}
