#include "client_service.h"

enum {
    BUFFER_SIZE = 40
};

ClientService::ClientService(ClientThreadInfo* info){
    thread_info = info;
}

bool ClientService::GetMessage(){
    char buf[BUFFER_SIZE];
    ssize_t bytes_read;
    message.clear();
    do{
        bytes_read = read(thread_info->client_socket,buf,BUFFER_SIZE);
        if(bytes_read == -1){
            std::cerr << "Error while trying to read from socket\n";
            return false;
        }
        for (int i = 0; i< bytes_read; ++i){
            message += buf[i];
        }
    }while (bytes_read > 0);
//    message = buf;
    return true;
}
void ClientService::PutMessageToLog(){
    thread_info->log_mutex->lock();
    thread_info->server->LogMessage(message);
    thread_info->log_mutex->unlock();
}
