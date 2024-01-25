#ifndef SERVER_HEADER_PARALLEL_1986
#define SERVER_HEADER_PARALLEL_1986
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <mutex>
#include <pthread.h>
#include <vector>

struct ClientThreadInfo{
    sockaddr_in client_address;
    int client_socket;
    class Server* server;
    std::mutex* log_mutex;
};

class Server{
public:
    Server(unsigned short socket_number, std::mutex* file_mutex);
    bool CreateSocket();
    bool ConnectToSocket();
    void StartListenToSocket();
    void AcceptConnection();
    void WorkWithClient();
    bool LogMessage(std::string message);

private:
    std::mutex* file_mutex;
    int listen_socket;
    int client_socket;
    sockaddr_in addres;
    sockaddr_in incoming_addres;
};

void* ClientThread(void* info);

#endif
