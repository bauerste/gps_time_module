#include <gtest/gtest.h>
#include "test/udp_test.cpp"
#include "test/nmea0183_test.cpp"

/**
 * Entry point for the test binary.  This function is called by the
 * C++ runtime library when the program is started.  It initializes the
 * Google Test framework and runs all registered tests.
 *
 * @param argc  The number of arguments passed to the program.
 * @param argv  An array of strings representing the arguments.
 *
 * @returns  The number of tests that failed.
 */
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}