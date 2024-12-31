#ifndef UDP_H
#define UDP_H

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class UDP {
public:
    UDP(int port, const std::string& address);
    ~UDP();

    void receiveData(std::string& data);
    void sendData(const std::string& data, const std::string& destinationAddress, int destinationPort);


    int getPort();
    std::string getAddress();
    bool isConnected();

    void close();
    void reconnect();
private:
    int m_sockfd;
    bool m_isConnected;
    std::string m_address;
    int m_port;
};

#endif  // UDP_H