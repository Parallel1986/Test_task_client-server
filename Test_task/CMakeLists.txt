cmake_minimum_required(VERSION 3.5)

project(Server-client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(client   client_main.cpp
                        client.cpp
                        client.h)

add_executable(server   server_main.cpp
                        server.cpp
                        client_service.cpp
                        client_service.h
                        server.h)
