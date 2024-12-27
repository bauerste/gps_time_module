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

    int getPort();
    std::string getAddress();
    bool isConnected();

    void close();
    void reconnect();
private:
    int sockfd_;
    bool isConnected_;
    std::string address_;
    int port_;
};

#endif  // UDP_H