#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <vector>
#include "device.h"
#include "protocol.h"

#define PORT 8000
#define BUFFER_SIZE 1024
#define CHUNK_SIZE 100

#pragma comment(lib, "ws2_32.lib")

void error_exit(const char* message) {
	std::cerr << message << "Error Code: " << WSAGetLastError() << std::endl;
	exit(EXIT_FAILURE);
}

int main() {
	WSADATA wsaData;
	SOCKET serverSocket, clientSocket;
	sockaddr_in serverAddr, clientAddr;
	int clientLen = sizeof(clientAddr);
	char buffer[BUFFER_SIZE];
	// initialize winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		error_exit("WSAStartup Failed");
	}

	// create socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET) {
		error_exit("Create socket failed!!");
		WSACleanup();
		return 1;
	}

	std::cout << "Socket is working!!" << std::endl;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(PORT);

	if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		error_exit("Bind failed!!");
		WSACleanup();
		return 1;
	}
	std::cout << "Bind is ok~~" << std::endl;

	listen(serverSocket, 5);
	std::cout << "Listening on port " << PORT << "...." << std::endl;

	while (true) {
		// Accept client connection
		clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientLen);
		if (clientSocket == INVALID_SOCKET) {
			error_exit("AcceptFailed!!");
			closesocket(serverSocket);
			WSACleanup();
			return 1;
		}
		std::cout << "Accepted from client is successful!!" << std::endl;

		int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
		if (bytesReceived > 0) {
			buffer[bytesReceived] = '\0';
			std::cout << "Message received from client: " << buffer << std::endl;

			// Send a response back to the client
			std::string response = "Hello from server!";
			if (send(clientSocket, response.c_str(), response.size(), 0) == SOCKET_ERROR) {
				std::cerr << "Failed to send message to client" << std::endl;
			}
			else {
				std::cout << "Message sent to client: " << response << std::endl;
			}
		}
		else {
			std::cerr << "Failed to receive message from client" << std::endl;
		}
	}

	closesocket(serverSocket);
	WSACleanup();
	return 0;
}