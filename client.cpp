#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h> 
#include <string>
#pragma comment(lib, "ws2_32.lib") 
int main() {
    WSADATA wsaData;
    int client_fd;
    struct sockaddr_in server_address;
    char buffer[1024] = {0};

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return -1;
    }

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);

    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    if (connect(client_fd, (struct sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        std::cerr << "Connection failed" << std::endl;
        closesocket(client_fd);
        WSACleanup();
        return -1;
    }

    std::cout << "Connected to server. You can start typing your messages." << std::endl;

    while (true) {
        std::string user_input;
        std::cout << "You: ";
        std::getline(std::cin, user_input);

        if (user_input == "exit") {
            break;
        }

        send(client_fd, user_input.c_str(), user_input.length(), 0);

        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead <= 0) {
            std::cerr << "Server disconnected or read failed." << std::endl;
            break;
        }

        std::cout << "Server: " << buffer << std::endl;
    }

    closesocket(client_fd);
    WSACleanup();

    return 0;
}
