cmake_minimum_required(VERSION 3.24)
project(MacroHardGameEngine)
set(CMAKE_CXX_STANDARD 17)

set(COMMON_SOURCES  "src/main.cpp" "include/IDisplay.h"  "include/ISystemLifeCycle.h" "src/SystemLifeCycle.h" "src/SystemLifeCycle.cpp" "include/IDisplaySystem.h" "include/ISystem.h")
set(PLATFORM_SOURCES )
if(UNIX)

elseif(WIN32)
list(
	APPEND PLATFORM_SOURCES 
	"src/Win32/Win32Display.cpp" 
	"src/Win32/Win32Display.h" 
	"src/Win32/GL/wglext.h" 
	"src/Win32/OpenGLDisplayWin32.h"
	"src/Win32/OpenGLDisplayWin32.cpp"
	"src/Win32/DisplaySystem.h"
	"src/Win32/DisplaySystem.cpp"
	"src/win32/Win32System.h" 
	"src/win32/Win32System.cpp"
)
endif()

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
add_executable(${PROJECT_NAME} ${COMMON_SOURCES}  ${PLATFORM_SOURCES})
else()
add_library(${PROJECT_NAME} STATIC ${COMMON_SOURCES}  ${PLATFORM_SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} "opengl32.lib" "MHTL")