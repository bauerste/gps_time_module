#include <iostream>
#include <chrono>
#include <memory>
#include "inc/udp_connector/udp_connector.h"
#include "inc/nmea_0183/nmea0183_parser.h"


int main() {
    std::unique_ptr<UDP> udpNMEA1083 = std::make_unique<UDP>(10110, "127.0.0.1");
    int count = 0;
    while (count < 100000) {
        std::string data;
        udpNMEA1083->receiveData(data);
        std::unique_ptr<NMEA0183Parser> parser = std::make_unique<NMEA0183Parser>();
        parser->parseMessage(data);
        count += 1;
    }

    return 0;
}