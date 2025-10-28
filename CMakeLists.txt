cmake_minimum_required(VERSION 3.14)

project(MilkSong VERSION 0.1 LANGUAGES CXX)

# allow out-of-source builds
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTING "Build tests" ON)

add_subdirectory(src)

#if(BUILD_TESTING)
#  enable_testing()
#  add_subdirectory(tests)
#endif()