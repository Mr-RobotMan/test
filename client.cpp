#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h> // For inet_addr
#pragma comment(lib, "ws2_32.lib") // Link with Ws2_32.lib

int main() {
    WSADATA wsaData;
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return -1;
    }

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation error" << std::endl;
        WSACleanup();
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // Convert IPv4 and IPv6 addresses from text to binary
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use inet_addr here

    // Check for address conversion error
    if (serv_addr.sin_addr.s_addr == INADDR_NONE) {
        std::cerr << "Invalid address" << std::endl;
        closesocket(sock);
        WSACleanup();
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        std::cerr << "Connection Failed" << std::endl;
        closesocket(sock);
        WSACleanup();
        return -1;
    }

    // Send message to server
    const char* message = "Hello from client!";
    send(sock, message, strlen(message), 0);

    // Receive server response
    recv(sock, buffer, sizeof(buffer), 0);
    std::cout << "Message from server: " << buffer << std::endl;

    // Close the socket
    closesocket(sock);
    WSACleanup();

    return 0;
}
