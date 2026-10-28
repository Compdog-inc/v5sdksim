cmake_minimum_required(VERSION 3.20)
project(v5sim LANGUAGES CXX C)

# Force GCC compiler
if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "This project requires the GCC compiler. Detected: ${CMAKE_CXX_COMPILER_ID}")
endif()

# Set C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set C17 standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Collect source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp")

# Define static library output (libv5sim.a)
add_library(v5sim STATIC ${SOURCES})

# Specify include directory
target_include_directories(v5sim
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Compiler warnings and options
target_compile_options(v5sim
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

add_subdirectory(simgui)

target_link_libraries(v5sim PRIVATE simgui_dynamic)
