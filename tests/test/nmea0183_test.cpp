#include <gtest/gtest.h>
#include "../../inc/nmea_0183/nmea0183_parser.h"

TEST(NMEAParseMessageTest, ValidGPZDA) {
  NMEA0183Parser parser;
  std::string message = "$GPZDA,123519.000,12,03,2023,00,00*6A";
  parser.parseMessage(message);
  // Verify output
  std::string expectedOutput = "UTC Date: 12-03-2023\nUTC Time: 12:35:19.000\n";
  std::stringstream actualOutput;
  std::cout.rdbuf(actualOutput.rdbuf());
  parser.parseMessage(message);
  std::cout.rdbuf(nullptr);
  EXPECT_EQ(expectedOutput, actualOutput.str());
}

TEST(NMEAParseMessageTest, InvalidGPZDA) {
  NMEA0183Parser parser;
  std::string message = "$GPZDB,123519,12,03,2023,00,00*6A";
  parser.parseMessage(message);
  // Verify no output
  std::string expectedOutput = "";
  std::stringstream actualOutput;
  std::cout.rdbuf(actualOutput.rdbuf());
  parser.parseMessage(message);
  std::cout.rdbuf(nullptr);
  EXPECT_EQ(expectedOutput, actualOutput.str());
}

TEST(NMEAParseMessageTest, EmptyMessage) {
  NMEA0183Parser parser;
  std::string message = "";
  parser.parseMessage(message);
  // Verify no output
  std::string expectedOutput = "Error: Empty NMEA message\n";
  std::stringstream actualOutput;
  std::cout.rdbuf(actualOutput.rdbuf());
  parser.parseMessage(message);
  std::cout.rdbuf(nullptr);
  EXPECT_EQ(expectedOutput, actualOutput.str());
}

TEST(NMEAParseMessageTest, MalformedMessageLessFields) {
  NMEA0183Parser parser;
  std::string message = "$GPZDA,1223519,12,03,2023";
  parser.parseMessage(message);
  // Verify no output
  std::string expectedOutput = "Error: Invalid NMEA message format: Expected 8 fields, received 5\n";
  std::stringstream actualOutput;
  std::cout.rdbuf(actualOutput.rdbuf());
  parser.parseMessage(message);
  std::cout.rdbuf(nullptr);
  EXPECT_EQ(expectedOutput, actualOutput.str());
}