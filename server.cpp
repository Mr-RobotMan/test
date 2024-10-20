#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h> // For inet_pton
#pragma comment(lib, "ws2_32.lib") // Link with Ws2_32.lib

int main() {
    WSADATA wsaData;
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return -1;
    }

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return -1;
    }

    // Set socket options
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    // Bind the socket to port 8080
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        std::cerr << "Bind failed" << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return -1;
    }

    // Listen for incoming connections
    listen(server_fd, 3);

    std::cout << "Waiting for connections..." << std::endl;

    // Accept an incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) == INVALID_SOCKET) {
        std::cerr << "Accept failed" << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return -1;
    }

    std::cout << "Connection established!" << std::endl;

    // Keep the connection open to receive and send multiple messages
    while (true) {
        // Clear the buffer
        memset(buffer, 0, sizeof(buffer));
        // Server remains unchanged but needs to keep the loop active
    while (true) {
        // Clear the buffer
        memset(buffer, 0, sizeof(buffer));

        // Read data from the client
        int bytesRead = recv(new_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead <= 0) {
            std::cerr << "Read failed or client disconnected." << std::endl;
            break; // Exit the loop if there's an issue
        }

        std::cout << "Message from client: " << buffer << std::endl;

        // Send a response
        std::string response = "Received: " + std::string(buffer);
        send(new_socket, response.c_str(), response.length(), 0);
}


    // Close the sockets
    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();

    return 0;
}
}