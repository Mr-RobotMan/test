Simple TCP Client-Server Communication (Windows, C++)
This repository contains a basic implementation of a TCP client and server using Winsock2 on Windows, written in C++.
Both the source code (client.cpp, server.cpp) and their corresponding compiled executables are included.

Contents
client.cpp — TCP client program

server.cpp — TCP server program

client.exe — Executable for client

server.exe — Executable for server

Requirements
Windows OS

C++ compiler (e.g., MSVC with Visual Studio, or g++ via MinGW)

Winsock2 (comes pre-installed with most Windows compilers)

How to Run
Start the Server

Run server.exe (or compile and run server.cpp).

The server will listen on port 8080 for incoming connections.

Start the Client

Run client.exe (or compile and run client.cpp).

The client will attempt to connect to 127.0.0.1:8080 (localhost).

Communication

After connecting, type your message in the client console and hit Enter.

The server will receive the message and respond with a confirmation ("Received: [your message]").

Type exit in the client to close the connection.
