cmake_minimum_required(VERSION 3.14)

# Test sources
add_executable(test_controller test_controller.cpp)

target_include_directories(test_controller PRIVATE
${PROJECT_SOURCE_DIR}/include
)

# Add dependencies
target_link_libraries(test_controller PRIVATE milk_lib)
target_link_libraries(test_controller PRIVATE gtest_main)
  
# Set asset folder as working directory for tests
set(TEST_ASSET_DIR ${PROJECT_SOURCE_DIR}/assets)

# Fetch google test 
FetchContent_Declare(
  GoogleTest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG main
)
FetchContent_MakeAvailable(GoogleTest)
include(GoogleTest)


gtest_discover_tests(
  test_controller
  WORKING_DIRECTORY ${TEST_ASSET_DIR}
)
