#include <gtest/gtest.h>
#include "../../inc/udp_connector/udp_connector.h"

// Verifies that the UDP constructor successfully sets the port and address fields.
TEST(UDPSuite, Constructor) {
    UDP udp(10110, "127.0.0.1");
    EXPECT_EQ(udp.getPort(), 10110);
    EXPECT_EQ(udp.getAddress(), "127.0.0.1");
}

// Verifies that receiveData successfully receives data from the UDP socket.
TEST(UDPSuite, ReceiveData) {
    UDP udp(10110, "127.0.0.1");
    std::string data;
    udp.receiveData(data);
    EXPECT_FALSE(data.empty()); // Assuming some data is received
}

// Verifies that reconnecting a UDP socket successfully reinitializes the socket and
// resets the connected flag.
TEST(UDPSuite, Reconnect) {
    UDP udp(10110, "127.0.0.1");
    udp.close();
    udp.reconnect();
    EXPECT_TRUE(udp.isConnected());
}

// Verifies that the UDP destructor successfully closes the socket and resets the connected flag.
TEST(UDPSuite, Destructor) {
    UDP udp(10110, "127.0.0.1");
    udp.~UDP(); // Explicitly call the destructor
    EXPECT_FALSE(udp.isConnected());
}
