# Build system info

## Requirements
-- mingw-64 installed somewhere on your pc. Link Here: https://www.mingw-w64.org/  
-- VSCode CMake extension  
-- A properly configured build profile in CMakePresets.json  


## Adding a build profile
I have gone ahead and added windows debug build profile for everyone in the CmakePresets.json file.
you will each need to find the profile with your name and alter the following lines to be the correct path to your mingw64 compilers.
```
       {
               "CMAKE_C_COMPILER": "C:/code/mingw64/bin/gcc.exe",
               "CMAKE_CXX_COMPILER": "C:/code/mingw64/bin/g++.exe",
       },
``` 

## How to Build
-- In VSCode press control+shift+p to open the command pallet  
-- run the command: CMAKE: RESET CMAKE TOOLS EXTENSION SUITE. (only way I can find to easily change build profile)  
-- once cmake resets it will ask you to select a profile. Select the one with your name  
-- press control+shift+p to open the command pallet again and run the command: CMAKE: install  


This should build the game using the selected profile and the copy the assets to the install folder  

## About build system
### CMakeLists.txt
This file contains all of the instructions for linking libraries and moving assets to the installation directory
```
cmake_minimum_required(VERSION 3.10)

# project name
project(CS370)

# add source files
set(SOURCES
    src/CS370.cpp
)

# create executable
add_executable(${PROJECT_NAME} ${SOURCES})

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
```

### CMakePresets.json
```
{
   "version": 8,
   "configurePresets": [
       {
           "name": "GCC_15.2.1_x86_64-pc-linux-gnu",
           "displayName": "Zacks Linux debug x86_64 GCC 15.2.1",
           "description": "Using compilers: C = /usr/bin/gcc, CXX = /usr/bin/g++",
           "binaryDir": "${sourceDir}/out/build/${presetName}",
           "cacheVariables": {
               "CMAKE_INSTALL_PREFIX": "${sourceDir}/out/install/${presetName}",
               "CMAKE_C_COMPILER": "/usr/bin/gcc",
               "CMAKE_CXX_COMPILER": "/usr/bin/g++",
               "CMAKE_BUILD_TYPE": "Debug"
           }
       },
       {
           "name": "Release_GCC_15.2.1_x86_64-pc-linux-gnu",
           "displayName": "Zacks Linux release x86_64 GCC 15.2.1",
           "description": "Using compilers: C = /usr/bin/gcc, CXX = /usr/bin/g++",
           "binaryDir": "${sourceDir}/out/build/${presetName}",
           "cacheVariables": {
               "CMAKE_INSTALL_PREFIX": "${sourceDir}/out/release/MilkSong",
               "CMAKE_C_COMPILER": "/usr/bin/gcc",
               "CMAKE_CXX_COMPILER": "/usr/bin/g++",
               "CMAKE_BUILD_TYPE": "Release"
           }
       },
       {
           "name": "GCC_15.2.0_x86_64-w64-mingw32",
           "displayName": "Zacks Win debug x86_64 GCC 15.2.0",
           "description": "Using compilers: C = C:\\code\\mingw64\\bin\\gcc.exe, CXX = C:\\code\\mingw64\\bin\\g++.exe",
           "generator": "MinGW Makefiles",
           "binaryDir": "${sourceDir}/out/build/${presetName}",
           "cacheVariables": {
               "CMAKE_INSTALL_PREFIX": "${sourceDir}/out/install/${presetName}",
               "CMAKE_C_COMPILER": "C:/code/mingw64/bin/gcc.exe",
               "CMAKE_CXX_COMPILER": "C:/code/mingw64/bin/g++.exe",
               "CMAKE_BUILD_TYPE": "Debug"
           }
       },
       {
           "name": "Release_GCC_15.2.0_x86_64-w64-mingw32",
           "displayName": "Zacks Win release x86_64 GCC 15.2.0",
           "description": "Using compilers: C = C:\\code\\mingw64\\bin\\gcc.exe, CXX = C:\\code\\mingw64\\bin\\g++.exe",
           "generator": "MinGW Makefiles",
           "binaryDir": "${sourceDir}/out/build/${presetName}",
           "cacheVariables": {
               "CMAKE_INSTALL_PREFIX": "${sourceDir}/out/release/MilkSong",
               "CMAKE_C_COMPILER": "C:/code/mingw64/bin/gcc.exe",
               "CMAKE_CXX_COMPILER": "C:/code/mingw64/bin/g++.exe",
               "CMAKE_BUILD_TYPE": "Release"
           }
       },
       {
           "name": "GCC_15.2.0_x86_64-w64-mingw32",
           "displayName": "Nicks Win debug x86_64 GCC 15.2.0",
           "description": "Using compilers: C = C:\\code\\mingw64\\bin\\gcc.exe, CXX = C:\\code\\mingw64\\bin\\g++.exe",
           "generator": "MinGW Makefiles",
           "binaryDir": "${sourceDir}/out/build/${presetName}",
           "cacheVariables": {
               "CMAKE_INSTALL_PREFIX": "${sourceDir}/out/install/${presetName}",
               "CMAKE_C_COMPILER": "C:/code/mingw64/bin/gcc.exe",
               "CMAKE_CXX_COMPILER": "C:/code/mingw64/bin/g++.exe",
               "CMAKE_BUILD_TYPE": "Debug"
           }
       },
              {
           "name": "GCC_15.2.0_x86_64-w64-mingw32",
           "displayName": "Kents Win debug x86_64 GCC 15.2.0",
           "description": "Using compilers: C = C:\\code\\mingw64\\bin\\gcc.exe, CXX = C:\\code\\mingw64\\bin\\g++.exe",
           "generator": "MinGW Makefiles",
           "binaryDir": "${sourceDir}/out/build/${presetName}",
           "cacheVariables": {
               "CMAKE_INSTALL_PREFIX": "${sourceDir}/out/install/${presetName}",
               "CMAKE_C_COMPILER": "C:/code/mingw64/bin/gcc.exe",
               "CMAKE_CXX_COMPILER": "C:/code/mingw64/bin/g++.exe",
               "CMAKE_BUILD_TYPE": "Debug"
           }
       },
              {
           "name": "GCC_15.2.0_x86_64-w64-mingw32",
           "displayName": "Alainas debug x86_64 GCC 15.2.0",
           "description": "Using compilers: C = C:\\code\\mingw64\\bin\\gcc.exe, CXX = C:\\code\\mingw64\\bin\\g++.exe",
           "generator": "MinGW Makefiles",
           "binaryDir": "${sourceDir}/out/build/${presetName}",
           "cacheVariables": {
               "CMAKE_INSTALL_PREFIX": "${sourceDir}/out/install/${presetName}",
               "CMAKE_C_COMPILER": "C:/code/mingw64/bin/gcc.exe",
               "CMAKE_CXX_COMPILER": "C:/code/mingw64/bin/g++.exe",
               "CMAKE_BUILD_TYPE": "Debug"
           }
       }
   ]
}
```