cmake_minimum_required(VERSION 3.10)

#project name
project(CS370)

#add source files
set(SOURCES
    src/CS370.cpp
)

#create executable
add_executable(${PROJECT_NAME} ${SOURCES})

#fetch raylib using FetchContent
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        master # Or a specific version tag like '4.5.0'
)
FetchContent_MakeAvailable(raylib)

# Platform-specific build steps
if(WIN32)
    target_link_libraries(${PROJECT_NAME} raylib winmm gdi32)
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

#move src to installation directory
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION .
    COMPONENT Runtime)

#move assets to installation directory
install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets
    DESTINATION .
    COMPONENT Runtime
    FILES_MATCHING PATTERN "*"
    PATTERN ".git*" EXCLUDE
    PATTERN "*.tmp" EXCLUDE
    PATTERN "*~" EXCLUDE)