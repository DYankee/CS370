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

# Platform-specific build steps
if(WIN32)
    add_custom_command( TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/assets ${CMAKE_INSTALL_PREFIX}/assets)
    find_library(RAYLIB_LIB raylib HINTS lib)
    target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIB})
    target_link_libraries(${PROJECT_NAME} winmm gdi32)
    if(NOT RAYLIB_LIB)
        message(FATAL_ERROR "raylib library not found in lib directory")
    endif()
elseif(UNIX)
    add_custom_command( TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} cp -r ${PROJECT_SOURCE_DIR}/assets ${CMAKE_INSTALL_PREFIX}/assets)
    target_link_libraries(${PROJECT_NAME} GL m pthread dl rt X11 raylib)
endif()