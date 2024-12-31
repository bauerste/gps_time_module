#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include "../inc/nmea_0183/nmea0183_parser.h"

NMEA0183Parser::NMEA0183Parser() {
    
}

NMEA0183Parser::~NMEA0183Parser() {
}

void NMEA0183Parser::parseMessage(const std::string &message) {

    std::string NMEASentence = message;

    if (message == "")
    {
        std::cout << "Error: Empty NMEA message" << std::endl;
        return;
    }
    
    // Split the string into substrings using "," as the delimiter
    std::vector<std::string> NMEAFields = splitStringByDelimiters(NMEASentence, ",*");

    if (NMEAFields[0] == "$GPZDA")
    {
        if (NMEAFields.size() == 8)
        {
            parseGPZDA(NMEAFields);
        }
        else
        {
            std::cout << "Error: Invalid NMEA message format: Expected 8 fields, received " << NMEAFields.size() << std::endl;
        }
        
    }
    else    
    {
        std::cout << "Error: Invalid NMEA message format: Expected $GPZDA, received " << NMEAFields[0] << std::endl;
        return;
    }
    
}

void NMEA0183Parser::parseGPZDA(std::vector<std::string> fields) {

    UTCDate date = parseUTCDate({fields[2], fields[3], fields[4]});
    if (!date.valid)
    {
        return;
    }
    

    std::cout << "UTC Date: ";
    std::cout  << std::setfill('0') << std::setw(2) << date.day << "-" << std::setfill('0') << std::setw(2)  << date.month << "-" << std::setfill('0') << std::setw(4) << date.year << std::endl;

    UTCTime time = parseUTCTime(fields[1]);
    if(!time.valid) return;

    std::cout << "UTC Time: ";
    std::cout << std::setfill('0') << std::setw(2) << time.hours << ":" << std::setfill('0') << std::setw(2) << time.minutes;
    std::cout << ":" << std::setfill('0') << std::setw(2)  << time.seconds << "." << std::setfill('0') << std::setw(3) << time.paddedFractionalSeconds << std::endl;

}

UTCTime NMEA0183Parser::parseUTCTime(const std::string &utcTimeField) 
{   
    UTCTime utctime;
    if (utcTimeField.length() == 10 || utcTimeField.length() == 6)
    {
        utctime.hours = std::stoi(utcTimeField.substr(0, 2));
        utctime.minutes = std::stoi(utcTimeField.substr(2, 2));
        utctime.seconds = std::stoi(utcTimeField.substr(4, 2));
        utctime.paddedFractionalSeconds = std::stoi(utcTimeField.substr(8, 3));
        utctime.valid = true;
        return utctime;
    } else
    {
        std::cout << "Error: Invalid UTC time format" << std::endl;
        utctime.valid = false;
        return utctime;
    }
    
    
    
}

UTCDate NMEA0183Parser::parseUTCDate(const std::vector<std::string> &utcDate)
{
    UTCDate utcdate;
    if (utcDate[0].length() != 2)
    {
        std::cout << "Error: Invalid UTC date day format" << std::endl;
        utcdate.valid = false;
        return utcdate;
    } else
    {
        utcdate.day = std::stoi(utcDate[0]);    
    }
    if (utcDate[1].length() != 2)
    {
        std::cout << "Error: Invalid UTC date month format" << std::endl;
        utcdate.valid = false;
        return utcdate;
    } else
    {
        utcdate.month = std::stoi(utcDate[1]);
    }
    if (utcDate[2].length() != 4)
    {
        std::cout << "Error: Invalid UTC date year format" << std::endl;
        utcdate.valid = false;
        return utcdate; 
    } else
    {
        utcdate.year = std::stoi(utcDate[2]);
    }
    utcdate.valid = true;
    return utcdate;
}

// Function to split a string by multiple delimiters
std::vector<std::string> NMEA0183Parser::splitStringByDelimiters(const std::string& inputString,
                                       const std::string& delimiters)
{

    std::vector<std::string> result; // Vector to store the split substrings
    int startPos = 0;
    int endPos = 0;

    // Loop until endPos is not equal to string::npos
    while ((endPos = inputString.find_first_of(delimiters,
                                               startPos))
           != std::string::npos) {

        if (endPos != startPos) { // Checking if the
                                  // substring is non-empty
            result.push_back(inputString.substr(
                startPos, endPos - startPos));
        }

        startPos
            = endPos + 1; // Update startPos to the position
                          // after the delimiter
    }

    // Extract the substring from startPos to the end of the
    // string and add it to result
    if (startPos != inputString.length()) {
        result.push_back(inputString.substr(startPos));
    }
    return result;
}

