///////////////////////////////////////////////////////////////////////////////
//        File: stub_server.cpp
// Description: Server class used by the stub for communication
//    Language: Visual C++
//    Platform: Windows 10 (visual studio 2017 Community)
// Application: Project 3, Multi-Node map reduce
//      Author: Bubah Conteh, BConteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "stub_server.h"

#define LOCALHOST_IP  "127.0.0.1"

Server::Server(int port, bool broadcastPublically) {
	// Initialize winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsok = WSAStartup(ver, &wsData);
	if (wsok != 0) {
		BOOST_LOG_TRIVIAL(error) << "Can't Initialize winsock! Quitting";
	}

	// Create a socket
	sListen_ = socket(AF_INET, SOCK_STREAM, NULL);
	if (sListen_ == INVALID_SOCKET) {
		BOOST_LOG_TRIVIAL(error) << "Can't create a scoket! Quitting";
		exit(1);
	}

	addr_.sin_family = AF_INET;
	addr_.sin_port = htons(port);
	addr_.sin_addr.s_addr = inet_addr(LOCALHOST_IP); // could use inet_pton

	bind(sListen_, (sockaddr*)&addr_, sizeof(addr_));

	listen(sListen_, SOMAXCONN);
}

bool Server::ListenForNewConnection() {

	SOCKET newConnection = accept(sListen_, (sockaddr*)&addr_, &addrlen_);

	if (newConnection == 0) //If accepting the client connection failed
	{
		BOOST_LOG_TRIVIAL(error) << 
			"Failed to accept the client's connection.";
		return false;
	}
	else {
		controller_socket_ = newConnection;
		BOOST_LOG_TRIVIAL(info) << "Client Connected!";
	}
}

bool Server::RecvMessage(std::string &message) {
	int bufferLength = 0;
	if (!RecvMessageLen(bufferLength)) {
		return false;
	}

	if (!RecvFullMessage(message, bufferLength)) {
		return false;
	}

	return true;
}

bool Server::RecvMessageLen(int &msg_length) {
	int retn_check = recv(controller_socket_, (char*)&msg_length,
		sizeof(int), NULL);

	if (retn_check == SOCKET_ERROR) {
		return false;
	}
	return true;
}

bool Server::RecvFullMessage(std::string &message, int total_bytes) {
	int bytes_recieved = 0;
	char* buffer = new char[total_bytes + 1];
	buffer[total_bytes] = '\0';
	while (bytes_recieved < total_bytes) {
		int returned_bytes = recv(controller_socket_, 
			buffer, total_bytes - bytes_recieved, NULL);

		if (returned_bytes == SOCKET_ERROR) {
			return false;
		}

		bytes_recieved += returned_bytes;
	}

	message = buffer;
	delete[] buffer;
	return true;
}
