cmake_minimum_required(VERSION 3.27)

project(SysCoreLibrary LANGUAGES CXX C)

# -- The user should decide that via the -DCMAKE_EXPORT_COMPILE_COMMANDS flag
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(syscore)

set_target_properties(syscore PROPERTIES 
    OUTPUT_NAME "syscore"
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF)

add_subdirectory(drivers)
add_subdirectory(kernel)