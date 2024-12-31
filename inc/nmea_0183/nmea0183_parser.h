#include <string>
#include <vector>

struct UTCTime
{
    int hours;
    int minutes;
    int seconds;
    int paddedFractionalSeconds;
    bool valid;
};

struct UTCDate
{
    int day;
    int month;
    int year;
    bool valid;
};



class NMEA0183Parser
{
public:
    NMEA0183Parser();
     ~NMEA0183Parser();

    void parseMessage(const std::string &message);

private:
    void parseGPZDA(std::vector<std::string> fields);
    
    std::vector<std::string> splitStringByDelimiters(const std::string &input, const std::string &delimiter);
    UTCTime parseUTCTime(const std::string &utcTime);
    UTCDate parseUTCDate(const std::vector<std::string> &utcDate);

};