#include "client.h"

int main(int argC, char** argV)
{
    if(argC != 4){
        std::cerr << "Incorrect number of arguments!\n";
        return 1;
    }
    std::string name = argV[1];
    unsigned short port = std::stoi(argV[2]);
    unsigned int time_interval = std::stoi(argV[3]);

    Client client(name,port,time_interval);
    while(true){
        if (!client.CreateSocket()
            || !client.ConnectToServer()){
            return 2;
        }
        client.SendMessage();
        client.CloseConnection();
        client.WaitDelay();
    }


    return 0;
}
