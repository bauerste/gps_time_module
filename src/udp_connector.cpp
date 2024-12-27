#include <iostream>

#include "../inc/udp_connector/udp_connector.h"

/**
 * Constructs a UDP object, creating and binding a UDP socket to the specified port and address.
 * 
 * @param port The port number to bind the UDP socket to.
 * @param address The IP address to bind the UDP socket to.
 * 
 * If the socket creation or binding fails, the constructor outputs an error message and exits the program.
 */
UDP::UDP(int port, const std::string& address) {
    sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd_ < 0) {
        std::cerr << "Error creating socket" << std::endl;
        exit(1);
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    inet_pton(AF_INET, address.c_str(), &serverAddress.sin_addr);

    if (bind(sockfd_, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        exit(1);
    }
    port_ = port;
    address_ = address;
    isConnected_ = true;
}
                                                                                                                                                               
/**
 * Closes the UDP socket.
 *
 * This is a virtual destructor, so it is automatically called when an UDP object is destroyed.
 */
UDP::~UDP() {
    close();
    isConnected_ = false;
}

/**
 * Receives data from the UDP socket.
 *
 * This function blocks until data is received. It uses the recvfrom system call
 * to read data from the socket into a buffer, and then assigns the received data
 * to the provided string reference.
 *
 * @param data A reference to a string where the received data will be stored.
 *
 * If an error occurs during data reception, an error message is printed to
 * standard error output, and the function returns without modifying the data.
 */
void UDP::receiveData(std::string& data) {
    if (!isConnected_) {
        reconnect();
    }


     // Set the receive timeout
    struct timeval tv;
    tv.tv_sec = 1000 / 1000;
    tv.tv_usec = (1000 % 1000) * 1000;
    setsockopt(sockfd_, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    char buffer[1024];
    socklen_t serverLength = sizeof(struct sockaddr_in);
    int bytesReceived = recvfrom(sockfd_, buffer, 1024, 0, (struct sockaddr*)NULL, &serverLength);
    if (bytesReceived < 0) {
        std::cerr << "Error receiving data" << std::endl;
        isConnected_ = false;
        return;
    }

    data.assign(buffer, bytesReceived);
}

/**
 * Reconnects the UDP socket.
 *
 * This function closes the current socket and attempts to create and bind a new
 * UDP socket to the stored port and address. If socket creation or binding fails,
 * an error message is printed and the program exits.
 */
void UDP::reconnect() {
    close();
    sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd_ < 0) {
        std::cerr << "Error creating socket" << std::endl;
        exit(1);
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port_);
    inet_pton(AF_INET, address_.c_str(), &serverAddress.sin_addr);

    if (bind(sockfd_, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        exit(1);
    }

    isConnected_ = true;
}

int UDP::getPort() {
    return port_;
}

std::string UDP::getAddress() {
    return address_;
}

void UDP::close() {
    if (sockfd_ != -1) {
        ::close(sockfd_);
        sockfd_ = -1;
    }
}

bool UDP::isConnected() {
    return isConnected_;
}