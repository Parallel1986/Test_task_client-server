### About
This is a test aplication for Linux, separated to two parts: client and server. Server requires number o port as the command line argument, client needs three arguments: name, port, delay between connections in seconds.

```
./server <port>
./client <client_name> <port> <time_delay>
```

The server openes the port and awaits connections. After a connection is established, server received a message from client in separate thread, writes the message to a log file and closes connection.
The client connects to the port and then send a message that containes current date and time and client`s name. Next, client closes the connection and waits for time that was passed via the command line argument and then repeat all actions again.

Project is builded with using CMake.
