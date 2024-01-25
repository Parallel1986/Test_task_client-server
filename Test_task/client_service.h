#ifndef CLIENT_SERVICE_PARALLEL_1986
#define CLIENT_SERVICE_PARALLEL_1986

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <mutex>
#include <unistd.h>
#include "server.h"

class ClientService{
public:
    ClientService(ClientThreadInfo* info);
    bool GetMessage();
    void PutMessageToLog();
private:
    ClientThreadInfo* thread_info;
    std::string message;
};

#endif
