

file(GLOB_RECURSE CPP_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*")
file(GLOB_RECURSE HEADER_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h*")

set(SOURCE_FILES ${CPP_FILES} ${HEADER_FILES})
message(DEBUG "${SOURCE_FILES}")
foreach(source IN LISTS SOURCE_FILES)    
	get_filename_component(source_path "${source}" PATH)
	string(REPLACE "/" "\\" source_path_msvc "${source_path}")
	source_group("${source_path_msvc}" FILES "${source}")
endforeach()
add_library(MicroHardGameEngine STATIC ${SOURCE_FILES})
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)




target_include_directories(MicroHardGameEngine INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)