cmake_minimum_required(VERSION 3.5)

project(2048 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
# User interface
		Ui/MainWindow.ui
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

target_include_directories(2048 PUBLIC Include
								PUBLIC Ui)
target_link_libraries(2048 PRIVATE Qt6::Widgets)

qt_finalize_executable(2048)
