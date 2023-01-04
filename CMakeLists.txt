cmake_minimum_required(VERSION 3.24)
project(MacroHardGameEngine)
add_subdirectory(libs)

add_executable(AAA main.cpp)
get_target_property(MHGEInclude MicroHardGameEngine INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(AAA
    PRIVATE
    ${MHGEInclude}
)