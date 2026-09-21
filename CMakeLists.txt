cmake_minimum_required(VERSION 3.20)
project(pros_sim LANGUAGES CXX)

# Force GCC compiler
if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "This project requires the GCC compiler. Detected: ${CMAKE_CXX_COMPILER_ID}")
endif()

# Set C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Collect source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Define static library output (libpros.a)
add_library(pros STATIC ${SOURCES})

# Specify include directory
target_include_directories(pros
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Compiler warnings and options
target_compile_options(pros
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
