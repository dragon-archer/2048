##
# @file    CMakeLists.txt
# @author  dragon-archer (dragon-archer@outlook.com)
# @brief   The CMake project file
# @version 0.0.1
#
# @license This file is published under The MIT License
#          See License in the root directory for details
#          Copyright (c) 2020 dragon-archer
#

cmake_minimum_required(VERSION 3.16) # For target_precompile_headers()
project(2048
        VERSION     0.0.1
        DESCRIPTION "2048 in terminal"
        LANGUAGES   CXX)

set(SRC
    src/main.cpp
    src/utility.cpp
    src/utility.h
    src/init.cpp
    src/init.h)
set(PCH
    src/pch.h)

add_executable(2048 ${SRC})
target_include_directories(2048 PRIVATE src/)
target_precompile_headers(2048 PRIVATE ${PCH})
# Set C++ standard to ISO C++11
target_compile_options(2048 PRIVATE
                       $<$<CXX_COMPILER_ID:GNU,Clang>:-std=c++11>
                       $<$<CXX_COMPILER_ID:MSVC>:/std:c++14>)     # NOTE: Because MSVC do not support /std:c++11, so set it to C++14

install(TARGETS 2048 DESTINATION bin)

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_DIRECTORY ${PROJECT_SOURCE_DIR}/pack)
set(CPACK_RESOURCE_FILE_LICENSE ${PROJECT_SOURCE_DIR}/LICENSE)
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_SOURCE_IGNORE_FILES
        ${PROJECT_SOURCE_DIR}/.git
        ${PROJECT_SOURCE_DIR}/.gitignore
        ${PROJECT_SOURCE_DIR}/.vscode
        ${PROJECT_SOURCE_DIR}/build
        ${PROJECT_SOURCE_DIR}/pack)
set(CPACK_PACKAGE_FILE_NAME ${PROJECT_NAME}-${PROJECT_VERSION})
set(CPACK_SOURCE_PACKAGE_FILE_NAME ${PROJECT_NAME}-${2048_VERSION}-src)
include(CPack)
