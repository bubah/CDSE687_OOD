///////////////////////////////////////////////////////////////////////////////
//        File: server.cpp
// Description: Provides a mechanism for processes to communicate messages
//    Language: Visual C++
//    Platform: MacBook Pro (Windows 10 Virtual Machine)
// Application: Project 3, Multi Node Map/Reduce Program
//      Author: Bubah Conteh, bconteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")

#include <winsock2.h>     // Windows sockets, ver 2
#include <WS2tcpip.h>     // support for IPv6 and other things
#include <iostream>

#include "server.h"

Server::Server(int port, bool broadcastPublically) {
	// Initialize winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsok = WSAStartup(ver, &wsData);
	if (wsok != 0) {
		BOOST_LOG_TRIVIAL(error) <<
			"Can't Initialize winsock! Quitting" << std::endl;
	}

	// Create a socket
	sListen_ = socket(AF_INET, SOCK_STREAM, NULL);
	if (sListen_ == INVALID_SOCKET) {
		BOOST_LOG_TRIVIAL(error) <<
			"Can't create a scoket! Quitting";
		exit(1);
	}

	addr_.sin_family = AF_INET;
	addr_.sin_port = htons(port);
	addr_.sin_addr.s_addr = inet_addr("127.0.0.1"); // could use inet_pton

	bind(sListen_, (sockaddr*)&addr_, sizeof(addr_));

	listen(sListen_, SOMAXCONN);
	serverptr = this;
}

bool Server::ListenForNewConnection() {
	SOCKET newConnection = accept(sListen_, (sockaddr*)&addr_, &addrlen_);

	if (newConnection == 0) {
		BOOST_LOG_TRIVIAL(error) << 
			"Failed to accept the client's connection." << std::endl;
		return false;
	}
	BOOST_LOG_TRIVIAL(info) << "Client Connected! ID:" << total_map_connections_;
	map_sockets_[total_map_connections_] = newConnection;

	return true;
}

bool Server::RecvMessage(int iD, std::string &message) {
	int bufferLength = 0;
	if (!RecvMessageLen(iD, bufferLength)) {
		return false;
	}

	if (!RecvFullMessage(iD, message, bufferLength)) {
		return false;
	}
	return true;
}

bool Server::RecvMessageType(int iD, int &msgType) {
	if (recv(map_sockets_[iD], (char*)&msgType, sizeof(int), NULL) == SOCKET_ERROR) {
		BOOST_LOG_TRIVIAL(error) << "Client::SendPacket():Socket error...";
		return false;
	}
	return true;
}

bool Server::RecvMessageLen(int iD, int &msg_length) {
	int retn_check = recv(map_sockets_[iD], (char*)&msg_length, sizeof(int), NULL);

	if (retn_check == SOCKET_ERROR) {
		BOOST_LOG_TRIVIAL(error) << "retn check error occured";
		return false;
	}
	return true;
}

bool Server::RecvFullMessage(int iD, std::string &message, int total_bytes) {
	int bytes_recieved = 0;
	char* buffer = new char[total_bytes + 1];
	buffer[total_bytes] = '\0';
	while (bytes_recieved < total_bytes) {
		int returned_bytes = recv(map_sockets_[iD], 
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

void Server::MapHandlerThread(int id, FNPTR_INT_STR_STR func) {
	while (true) {
		std::string message;
		std::string msgType;

		if (!serverptr->RecvMessage(id, msgType)) {
			break;
		}

		if (!serverptr->RecvMessage(id, message)) {
			break;
		}

		func(id, msgType, message);
	}
	BOOST_LOG_TRIVIAL(info) << "Lost Connection to Map ID: " << id;
}

void Server::ReduceHandlerThread(int id, FNPTR_INT_STR_STR func) {
	while (true) {
		std::string message;
		std::string msgType;

		if (!serverptr->RecvMessage(id, msgType)) {
			break;
		}

		if (!serverptr->RecvMessage(id, message)) {
			break;
		}

		func(id, msgType, message);
	}
	BOOST_LOG_TRIVIAL(info) << "Lost Connection to Reduce ID: " << id;
}

void Server::TotalConnectIncrementor() {
	total_map_connections_++;
}

int Server::GetNumOfConnections() {
	return total_map_connections_;
}

void Server::SetNumMapsRunning(int num) {
	num_maps_run_ = num;
}

void Server::SetNumReduceRunning(int num) {
	num_reduce_run_ = num;
}

bool Server::MapIsRunning() {
	return maps_running_;
}
bool Server::ReduceIsRunning() {
	return red_running_;
}
