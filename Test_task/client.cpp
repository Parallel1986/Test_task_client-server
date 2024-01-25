#include "client.h"
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <time.h>

Client::Client(std::string name,unsigned short server_port, unsigned int time_to_connect){
    this->name = name;
    reconnect_time = time_to_connect;

    address.sin_family = AF_INET;
    address.sin_port = htons(server_port);
    address.sin_addr.s_addr = htonl(INADDR_ANY);
}

Client::~Client(){
    if (socket_desc != -1){
        close(socket_desc);
    }
}

bool Client::CreateSocket(){
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1){
        std::cerr << "Client " << name << " unable to create socket\n";
        return false;
    }
    return true;
}

bool Client::ConnectToServer(){
    if(connect(socket_desc, (struct sockaddr*)&address,sizeof(address)) == -1){
        std::cerr << "Error while trying to establish connection\n";
        return false;
    }
    return true;
}

void Client::SendMessage(){
    std::string message = GetTimeString() + " " + name + "\0";
    write(socket_desc,message.c_str(),message.size());
}

void Client::CloseConnection(){
    close(socket_desc);
}

void Client::WaitDelay(){
    sleep(reconnect_time);
}

std::string Client::GetTimeString(){
    std::string result;
    auto sys_time = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(sys_time);
    auto mils = std::chrono::duration_cast<std::chrono::milliseconds>(sys_time.time_since_epoch()).count() - time * 1000;
    std::tm time_struct = *std::localtime(&time);
    char buff[40];
    strftime(buff,40,"[%F %T", &time_struct);
    result = buff;
    result += "." + std::to_string(mils) + "]";
    return result;
}
