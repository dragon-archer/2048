cmake_minimum_required(VERSION 3.5)

project(2048 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WITH_STATIC_QT)
	if(NOT QT_STATIC_PATH)
		message(FATAL_ERROR "Please specify the path to Qt static build.")
	endif()
	message(STATUS "Building with static Qt at ${QT_STATIC_PATH}")
	set(CMAKE_PREFIX_PATH ${QT_STATIC_PATH}/lib/cmake)
endif()
find_package(Qt6 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES Language/2048_zh_CN.ts)

set(PROJECT_SOURCES
# Source files
		Source/Common.cpp
		Source/Main.cpp
		Source/MainWindow.cpp
# Header files
		Include/Pch.h
		Include/Common.h
		Include/MainWindow.h
# Resource files
		Resource.qrc
# Translation files
		${TS_FILES}
)

qt_add_executable(2048
	MANUAL_FINALIZATION
	${PROJECT_SOURCES}
)
qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_include_directories(2048 PRIVATE Include)

set(QT_LIBS Qt6::Widgets)
set(QT_LINK_LIBS b2 zstd)
if(WITH_STATIC_QT)
	target_link_directories(2048 PRIVATE ${QT_STATIC_PATH}/lib)
	target_link_libraries(2048 PRIVATE -static ${QT_LIBS} ${QT_LINK_LIBS})
else()
	target_link_libraries(2048 PRIVATE ${QT_LIBS} ${QT_LINK_LIBS})
endif()

# Disable console
if(APPLE)
	set_target_properties(${PROJECT_NAME} PROPERTIES
		MACOSX_BUNDLE YES
	)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set_target_properties(${PROJECT_NAME} PROPERTIES
		WIN32_EXECUTABLE YES
		LINK_FLAGS "/ENTRY:mainCRTStartup"
	)
	# Fix MSVC
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus /permissive-")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
else()
	message(SEND_ERROR "You are using an unsupported compiler (Not GCC, Clang or MSVC)")
endif()

qt_finalize_executable(2048)
