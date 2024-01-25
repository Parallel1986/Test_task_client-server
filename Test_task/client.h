#ifndef CLIENT_HEADER_PARALLEL1986
#define CLIENT_HEADER_PARALLEL1986
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

class Client{
public:
    Client(std::string name,unsigned short server_port, unsigned int time_to_connect = 1);
    ~Client();
    bool ConnectToServer();
    bool CreateSocket();
    void SendMessage();
    void CloseConnection();
    void WaitDelay();
private:
    std::string GetTimeString();
    int socket_desc = -1;
    sockaddr_in address;
    unsigned int reconnect_time;
    std::string name;
};

#endif
