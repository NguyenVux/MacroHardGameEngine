

set(COMMON_SOURCES  "src/main.cpp" "include/IDisplay.h" )
set(PLATFORM_SOURCES)
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
)
endif()
add_library(${PROJECT_NAME} STATIC ${COMMON_SOURCES}  ${PLATFORM_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} "opengl32.lib")