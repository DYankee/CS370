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
   find_library(RAYLIB_LIB raylib HINTS lib)
   target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIB})
   target_link_libraries(${PROJECT_NAME} winmm gdi32)
   if(NOT RAYLIB_LIB)
       message(FATAL_ERROR "raylib library not found in lib directory")
   endif()
elseif(UNIX)
   target_link_libraries(${PROJECT_NAME} GL m pthread dl rt X11 raylib)
endif()

# Release-specific optimizations
if(CMAKE_BUILD_TYPE STREQUAL "Release")
   # Strip debug symbols on Unix-like systems
   if(UNIX)
       add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
           COMMAND strip $<TARGET_FILE:${PROJECT_NAME}>
           COMMENT "Stripping debug symbols from release binary")
   endif()
endif()

install(TARGETS ${PROJECT_NAME}
   RUNTIME DESTINATION .
   COMPONENT Runtime)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets
   DESTINATION .
   COMPONENT Runtime
   FILES_MATCHING PATTERN "*"
   PATTERN ".git*" EXCLUDE
   PATTERN "*.tmp" EXCLUDE
   PATTERN "*~" EXCLUDE)