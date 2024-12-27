file(GLOB TEST_SOURCES *.cpp)
add_executable(gtest_main main_test.cpp ${TEST_SOURCES} ../../src/udp_connector.cpp ../../src/nmea0183_parser.cpp)

target_link_libraries(gtest_main gtest pthread)

include_directories(../../inc)

