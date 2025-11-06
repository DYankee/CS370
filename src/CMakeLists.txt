# Build library and executable for MilkSong

cmake_minimum_required(VERSION 3.14)

set(MILK_SOURCES
    components/enemy_stats.cpp
    components/physics_object.cpp
    components/player_stats.cpp
    components/sprite_data.cpp
    components/animation.cpp
    components/enemy_behavior.cpp
    entities/camera.cpp
    entities/enemy.cpp
    entities/map.cpp
    entities/player.cpp
    entities/health_upgrade.cpp
    systems/asset_loader.cpp
    systems/collision_system.cpp
    systems/player_controller.cpp
    systems/map_manager.cpp
    systems/camera_controller.cpp
    systems/iframes_system.cpp
    systems/hud_system.cpp
    systems/player_enemy_collision.cpp
    systems/enemy_controller.cpp
    systems/health_upgrade_controller.cpp
    systems/player_health_upgrade_collision.cpp
)

add_library(milk_lib STATIC ${MILK_SOURCES})

target_include_directories(milk_lib PUBLIC
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/include
)

# Fetch raylib
include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG master
)
FetchContent_MakeAvailable(raylib)

target_link_libraries(milk_lib PUBLIC raylib)

# Create executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE milk_lib)

# Platform specific libraries
if(WIN32)
  # target_link_libraries(${PROJECT_NAME} PRIVATE winmm gdi32)
elseif(UNIX)
  target_link_libraries(${PROJECT_NAME} PRIVATE GL m pthread dl rt X11)
endif()

