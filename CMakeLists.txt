cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)

set(COMMON_SOURCES  "src/main.cpp" "include/IDisplay.h" )
set(PLATFORM_SOURCES )
if(UNIX)

elseif(WIN32)
list(
	APPEND PLATFORM_SOURCES 
	"src/Win32/Win32Display.cpp" 
	"src/Win32/Win32Display.h" 
	"src/Win32/GL/gl.c" 
	"src/Win32/GL/wgl.c" 
	"src/Win32/GL/wglext.h" 
	"src/Win32/GL/glad/gl.h" 
	"src/Win32/GL/glad/wgl.h"
	"src/Win32/OpenGLDisplayWin32.h"
	"src/Win32/OpenGLDisplayWin32.cpp"
)
endif()

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
project(MacroHardGameEngine)
add_executable(${PROJECT_NAME} ${COMMON_SOURCES}  ${PLATFORM_SOURCES})
else()
add_library(${PROJECT_NAME} STATIC ${COMMON_SOURCES}  ${PLATFORM_SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} "opengl32.lib")