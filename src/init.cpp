/**
 * @file    src/init.cpp
 * @author  dragon-archer (dragon-archer@outlook.com)
 * @brief   Init global settings
 * @version 0.0.1
 * 
 * @license This file is published under The MIT License
 *          See License in the root directory for details
 *          Copyright (c) 2020 dragon-archer
 */

#include <pch.h>
#include <init.h>

/**
 * @brief  Init global settings
 * 
 * @return true  Init success
 * @return false Init failure
 */
void init()
{
	////////////////////////////////////////
	///////////// Print margin /////////////
	////////////////////////////////////////
	int row, col;
	getsize(row, col);
	cls();
	gotoxy(0, 0);
	std::fill_n(std::ostream_iterator<char>(std::cout), col, '#');
	gotoxy(0, 0);
	std::fill_n(
		std::ostream_iterator<char>(
			std::cout, 
			std::string('#' + std::string(col - 2, ' ') + '#').c_str()
		),
		row - 2,
		'\n'
	);
	std::fill_n(std::ostream_iterator<char>(std::cout), col, '#');
}
