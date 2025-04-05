#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <vector>
#include <mutex>
#include "device.h"
#include "protocol.h"

#define PORT 8000
#define BUFFER_SIZE 1024
#define CHUNK_SIZE 100

#pragma comment(lib, "ws2_32.lib")

std::mutex deviceMutex; // protects shared device data
std::map<std::string, Device> devices;

void error_exit(const char* message) {
	std::cerr << message << "Error Code: " << WSAGetLastError() << std::endl;
	exit(EXIT_FAILURE);
}

void handleClient(SOCKET clientSocket) {
	char buffer[BUFFER_SIZE];
	while (true) {
		int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
		if (bytesReceived <= 0) {
			break; // Client disconnected
		}
		buffer[bytesReceived] = '\0';
		std::string command(buffer);

		std::string response;
		{
			std::lock_guard<std::mutex> lock(deviceMutex);
			response = processCmd(command, devices); // process command
		}
		send(clientSocket, response.c_str(), response.length(), 0);
		std::cout << "Command: " << command << " | Response: " << response;
	}
	closesocket(clientSocket);
	std::cout << "Client disconnected." << std::endl;
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
	
	initializeDevices(devices);
	std::vector<std::thread> threads;
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

		threads.push_back(std::thread(handleClient, clientSocket));
	}

	for (auto& t : threads) t.join();

	closesocket(serverSocket);
	WSACleanup();
	return 0;
}