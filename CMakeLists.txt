cmake_minimum_required(VERSION 3.10)

# Project name
project(CS370)

# Add source files
set(SOURCES
    src/CS370.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    include    
)

# Find and link raylib
find_library(RAYLIB_LIB raylib HINTS lib)
if(NOT RAYLIB_LIB)
    message(FATAL_ERROR "raylib library not found in lib directory")
endif()

target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIB})

# Platform-specific libraries that raylib needs
if(WIN32)
    target_link_libraries(${PROJECT_NAME} winmm gdi32)
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} 
        "-framework OpenGL" 
        "-framework Cocoa" 
        "-framework IOKit" 
        "-framework CoreVideo"
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} GL m pthread dl rt X11)
endif()