# CMakeList.txt : CMake project for CS370, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CS370 "CS370.cpp" "CS370.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CS370 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
