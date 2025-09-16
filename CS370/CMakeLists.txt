# CMakeList.txt : CMake project for CS370, include source and define
# project specific logic here.
#

find_package(raylib 5.5 QUIET)
include(FetchContent)
if (NOT raylib_FOUND)
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP True #This option is not required but suppresses a warning
    )
    FetchContent_MakeAvailable(raylib)
endif()

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


# Add source to this project's executable.
add_executable (CS370 "CS370.cpp" "CS370.h")
target_link_libraries(${PROJECT_NAME} raylib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CS370 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
