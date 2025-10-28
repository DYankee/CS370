cmake_minimum_required(VERSION 3.10)

# project name
project(CS370)

# add source files
set(SOURCES
    src/CS370.cpp
)

# Add component, entity, and system sources
list(APPEND SOURCES
    src/components/physics_object.cpp
    src/components/player_stats.cpp
    src/components/sprite_data.cpp
    src/entities/camera.cpp
    src/entities/map.cpp
    src/entities/player.cpp
    src/systems/asset_loader.cpp
    src/systems/collision_system.cpp
    src/systems/player_controller.cpp
    src/systems/map_manager.cpp
    src/systems/camera_controller.cpp
    src/systems/hud_system.cpp
    src/systems/iframes_system.cpp
)

# create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Make sure the compiler can find project headers under src/ and include/
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

# fetch raylib using FetchContent
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        master # Or a specific version tag like '4.5.0'
)
FetchContent_MakeAvailable(raylib)

# platform-specific build steps
if(WIN32)
    target_link_libraries(${PROJECT_NAME} raylib winmm gdi32)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} GL m pthread dl rt X11 raylib)
endif()

# release-specific optimizations
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Strip debug symbols on Unix-like systems
    if(UNIX)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND strip $<TARGET_FILE:${PROJECT_NAME}>
            COMMENT "Stripping debug symbols from release binary")
    endif()
endif()

# move src to installation directory
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION .
    COMPONENT Runtime)

# move assets to installation directory
install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets
    DESTINATION .
    COMPONENT Runtime
    FILES_MATCHING PATTERN "*"
    PATTERN ".git*" EXCLUDE
    PATTERN "*.tmp" EXCLUDE
    PATTERN "*~" EXCLUDE)