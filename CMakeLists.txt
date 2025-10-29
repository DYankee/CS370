cmake_minimum_required(VERSION 3.14)
project(MilkSong)

# Build src directory
add_subdirectory(src)

# Build tests
option(BUILD_TESTING "Build tests" ON)
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

# move target to installation dir
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION . COMPONENT Runtime)

# move assets to installation dir
install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets
    DESTINATION .
    COMPONENT Runtime
    FILES_MATCHING PATTERN "*"
    PATTERN ".git*" EXCLUDE
    PATTERN "*.tmp" EXCLUDE
    PATTERN "*~" EXCLUDE)