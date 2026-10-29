
cmake_minimum_required(VERSION 3.25)

project(simgui LANGUAGES C CXX)

# Force GCC compiler
if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "This project requires the GCC compiler. Detected: ${CMAKE_CXX_COMPILER_ID}")
endif()

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

FetchContent_Declare(SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.18
    GIT_SHALLOW 1
)

set(SDL_SHARED OFF CACHE BOOL "SDL_SHARED")
set(SDL_STATIC ON CACHE BOOL "SDL_STATIC")
FetchContent_MakeAvailable(SDL3)

if(LINUX)
    target_compile_definitions(SDL3-static PUBLIC
        SDL_VIDEO_DRIVER_X11=1
        NOMINMAX
    )
endif()

FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.93.0-docking
    GIT_SHALLOW 1
)
FetchContent_MakeAvailable(imgui)

set(imgui_SOURCES
   ${imgui_SOURCE_DIR}/imgui.cpp
   ${imgui_SOURCE_DIR}/imgui_demo.cpp
   ${imgui_SOURCE_DIR}/imgui_draw.cpp
   ${imgui_SOURCE_DIR}/imgui_tables.cpp
   ${imgui_SOURCE_DIR}/imgui_widgets.cpp
   ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
   ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
   ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlgpu3.cpp
)

set(imgui_HEADERS
    ${imgui_SOURCE_DIR}/imgui.h
    ${imgui_SOURCE_DIR}/imstb_rectpack.h
    ${imgui_SOURCE_DIR}/imstb_truetype.h
    ${imgui_SOURCE_DIR}/imgui_internal.h
    ${imgui_SOURCE_DIR}/imstb_textedit.h
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.h
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlgpu3.h
    ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.h
)

add_library(imgui ${imgui_HEADERS} ${imgui_SOURCES})

target_include_directories(imgui
    PUBLIC
    $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>
    "../include"
)

target_link_libraries(imgui
    PUBLIC
    SDL3::SDL3
)

target_compile_definitions(imgui
    PUBLIC
    # IMGUI_DISABLE_DEFAULT_FONT
    IMGUI_DISABLE_OBSOLETE_FUNCTIONS
)

add_library(simgui_dynamic SHARED
    src/simgui.cpp
    src/api.cpp
)

set_target_properties(simgui_dynamic PROPERTIES
    OUTPUT_NAME simgui
    WINDOWS_EXPORT_ALL_SYMBOLS OFF
)

target_link_libraries(simgui_dynamic PUBLIC
    imgui
    SDL3::SDL3
    # DO NOT LINK v5sim!!!
    # IT NEEDS TO GET THE FUNCTION TABLES FROM THE MAIN ROBOT CODE
)

target_include_directories(simgui_dynamic PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_definitions(simgui_dynamic PUBLIC
    AS_LIBRARY
)

add_executable(simgui
    src/simgui.cpp
    src/main.cpp
)

target_link_libraries(simgui PRIVATE
    imgui
    SDL3::SDL3
)

target_include_directories(simgui PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if(MSVC)
    target_compile_options(simgui PRIVATE /W4 /permissive-)
else()
    target_compile_options(simgui PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()
