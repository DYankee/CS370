cmake_minimum_required(VERSION 3.14)

# Test sources
add_executable(Test_controller test_controller.cpp)

target_include_directories(Test_controller PRIVATE
  ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(Test_controller PRIVATE milk_lib)

# Ensure assets are available as working directory for tests
set(TEST_ASSET_DIR ${PROJECT_SOURCE_DIR}/assets)

add_test(NAME test_controller COMMAND Test_controller)
set_tests_properties(test_controller PROPERTIES WORKING_DIRECTORY ${TEST_ASSET_DIR})
