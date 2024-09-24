# CMakeList.txt : CMake project for Win32Frame, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Win32Frame WIN32 "Win32Frame.cpp" "Win32Frame.h" "framework.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Win32Frame PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
#target_compile_definitions(Win32Frame PRIVATE "UNICODE;_UNICODE")


