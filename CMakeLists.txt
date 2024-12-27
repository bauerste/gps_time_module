cmake_minimum_required(VERSION 3.10)
project(gps_time_module)

# Set the C++ standard to C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directory
include_directories(inc)

# Add the source files
add_executable(gps_time_module main.cpp src/udp_connector.cpp src/nmea0183_parser.cpp)

# Link the necessary libraries
target_link_libraries(gps_time_module pthread)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


# Add the test directory to the include path
add_subdirectory(tests)