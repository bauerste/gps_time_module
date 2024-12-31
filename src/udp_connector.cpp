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
    m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        exit(1);
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    inet_pton(AF_INET, address.c_str(), &serverAddress.sin_addr);

    if (bind(m_sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        exit(1);
    }
    m_port = port;
    m_address = address;
    m_isConnected = true;
}
                                                                                                                                                               
/**
 * Closes the UDP socket.
 *
 * This is a virtual destructor, so it is automatically called when an UDP object is destroyed.
 */
UDP::~UDP() {
    close();
    m_isConnected = false;
}

/**
 * Sends the given data to the specified destination address and port.
 * 
 * @param data The data to be sent.
 * @param destinationAddress The destination IP address.
 * @param destinationPort The destination port number.
 * 
 * If the send operation fails, the function outputs an error message.
 */
void UDP::sendData(const std::string& data, const std::string& destinationAddress, int destinationPort) {
    struct sockaddr_in destinationAddress_;
    destinationAddress_.sin_family = AF_INET;
    destinationAddress_.sin_port = htons(destinationPort);
    inet_pton(AF_INET, destinationAddress.c_str(), &destinationAddress_.sin_addr);

    int bytesSent = sendto(m_sockfd, data.c_str(), data.length(), 0, (struct sockaddr*)&destinationAddress_, sizeof(destinationAddress_));
    if (bytesSent < 0) {
        std::cerr << "Error sending data" << std::endl;
    }
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
    if (!m_isConnected) {
        reconnect();
    }


     // Set the receive timeout
    struct timeval tv;
    tv.tv_sec = 1000 / 1000;
    tv.tv_usec = (1000 % 1000) * 1000;
    setsockopt(m_sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    char buffer[1024];
    socklen_t serverLength = sizeof(struct sockaddr_in);
    int bytesReceived = recvfrom(m_sockfd, buffer, 1024, 0, (struct sockaddr*)NULL, &serverLength);
    if (bytesReceived < 0) {
        std::cerr << "Error receiving data" << std::endl;
        m_isConnected = false;
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
    m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        exit(1);
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(m_port);
    inet_pton(AF_INET, m_address.c_str(), &serverAddress.sin_addr);

    if (bind(m_sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        exit(1);
    }

    m_isConnected = true;
}

int UDP::getPort() {
    return m_port;
}

std::string UDP::getAddress() {
    return m_address;
}

void UDP::close() {
    if (m_sockfd != -1) {
        ::close(m_sockfd);
        m_sockfd = -1;
    }
}

bool UDP::isConnected() {
    return m_isConnected;
}