#include <unistd.h>
#include "server.h"
#include "client_service.h"

int main(int argC, char** argV)
{
    if (argC != 2){
        std::cerr << "Incorrect number of arguments!\n";
        return 1;
    }
    unsigned short port = std::stoi(argV[1]);
    std::mutex server_mutex;

    Server server(port, &server_mutex);
    if (!server.CreateSocket()
        || !server.ConnectToSocket()){
        return 2;
    }
    server.StartListenToSocket();

    while (true) {
        server.AcceptConnection();
        server.WorkWithClient();
    }
    return 0;
}
