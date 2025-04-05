#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>

#define PORT 8000
#define BUFFER_SIZE 1024
#define IP "127.0.0.1"

#pragma comment(lib, "ws2_32.lib")

void error_exit(const char* message) {
    std::cerr << message << " Error Code: " << WSAGetLastError() << std::endl;
    WSACleanup();
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();
    exit(EXIT_FAILURE);
}

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        error_exit("WSAStartup Failed");
    }

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        error_exit("Socket creation failed");
    }

    // Setup server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, IP, &serverAddr.sin_addr) <= 0) {
        error_exit("Invalid address");
    }

    // Connect to server
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        error_exit("Connection failed");
    }

    std::cout << "Connected to server!" << std::endl;

    std::string command;
    while (true) {
        std::cout << "Enter command (or 'exit' to quit): ";
        std::getline(std::cin, command);
        if (command == "exit") break;

        send(clientSocket, command.c_str(), command.length(), 0);

        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::cout << "Server response: " << buffer << std::endl;
        }
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
