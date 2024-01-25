#include "server.h"
#include "client_service.h"

enum {
    QUEUE_SIZE = 64
};

Server::Server(unsigned short socket_number,std::mutex* file_mutex){
    addres.sin_family = AF_INET;
    addres.sin_port = htons(socket_number);
    addres.sin_addr.s_addr = htonl(INADDR_ANY);
    this->file_mutex = file_mutex;
}

Server::~Server(){

}

bool Server::ConnectToSocket(){
    if(bind(listen_socket, (struct sockaddr *)&addres,sizeof(addres)) == -1){
        std::cerr << "Error while trying to bind socket\n";
        return false;
    }
    return true;
}

bool Server::CreateSocket(){
    listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_socket == -1){
        std::cerr << "Error while creating socket\n";
        return false;
    }
    int opt = 1;
    setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    return true;
}

void Server::StartListenToSocket(){
    listen(listen_socket, QUEUE_SIZE);
}
void Server::AcceptConnection(){
    socklen_t s_t = sizeof (incoming_addres);
    client_socket = accept(listen_socket, (sockaddr*)&incoming_addres, &s_t);
}

bool Server::LogMessage(std::string message){
    std::ofstream log_file;
    log_file.open("log.txt", std::ios::binary | std::ios::app);
    if(log_file.is_open()){
        log_file << message << "\n";
        log_file.close();
    }
    else {
        return false;
    }
    return true;
}
std::mutex* Server::GetMutex(){
    return file_mutex;
}
sockaddr_in Server::GetClientAddress(){
    return incoming_addres;
}

void Server::WorkWithClient(){
    ClientThreadInfo* info = new ClientThreadInfo;
    info->client_address = incoming_addres;
    info->client_socket = client_socket;
    info->log_mutex = file_mutex;
    info->server = this;

    pthread_t thread_id;
    if (pthread_create(&thread_id,NULL,*ClientThread,info)==0){
        thread_list.push_back(thread_id);
        pthread_detach(thread_id);
    }
    else{
        std::cerr << "Error while creating thread\n";
        delete info;
    }
}

void* ClientThread(void* info){
    ClientThreadInfo thread_info = *((ClientThreadInfo*) info);
    delete (ClientThreadInfo*)info;
    ClientService service(&thread_info);
    if(service.GetMessage()){
        service.PutMessageToLog();
    }
    close(thread_info.client_socket);
    return nullptr;
}
