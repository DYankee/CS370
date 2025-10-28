# Tests CMake

cmake_minimum_required(VERSION 3.14)

# Test sources
add_executable(TestInstantiator test_controller.cpp assets.cpp)

target_include_directories(TestInstantiator PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(TestInstantiator PRIVATE milk_lib)

# Ensure assets are available as working directory for tests
set(TEST_ASSET_DIR ${PROJECT_SOURCE_DIR}/assets)

add_test(NAME test_controller COMMAND TestInstantiator)
set_tests_properties(test_controller PROPERTIES WORKING_DIRECTORY ${TEST_ASSET_DIR})
