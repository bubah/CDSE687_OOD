///////////////////////////////////////////////////////////////////////////////
//        File: client.cpp
// Description: Connects to the server for packet communications between the
//              controller and Map/Reduce processes and with the stub.
//    Language: Visual C++
//    Platform: MacBook Pro (Windows 10 Virtual Machine)
// Application: Project 3, Single Node Map/Reduce Program
//      Author: Rob Hardisty/Bubah Conteh, rlhardis@syr.edu/bconteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#include <boost/log/trivial.hpp>

#pragma comment(lib,"ws2_32.lib") // Windows sockets, ver 2
#include <WS2tcpip.h>     // support for IPv6 and other things
#include <iostream>
#include <mutex>

#include "client.h"

static std::mutex mtx;

Client::Client(const std::string ip, int port) {
	// Initialize winsock
	WSADATA ws_data;
	WORD ver = MAKEWORD(2, 2);
	int wsok = WSAStartup(ver, &ws_data);
	if (wsok != 0) {
        BOOST_LOG_TRIVIAL(error) 
		<< "Client::Client(): Winsock initialization "
        "error. Quitting!";
		exit(0);
	}
	// fill in the hint structure
	int sizeofaddr = sizeof(addr_); // length of address (req'd for accept call)
	inet_pton(AF_INET, ip.c_str(), &addr_.sin_addr); //
	addr_.sin_port = htons(port); // Port
	addr_.sin_family = AF_INET; // IPv4 Socket
}
// Create a socket and connects
bool Client::Connect() {
	stub_connection_ = socket(AF_INET, SOCK_STREAM, 0);
	if (stub_connection_ == INVALID_SOCKET) {
        BOOST_LOG_TRIVIAL(error) << "Client::Connect: Cannot create socket! "
			<< WSAGetLastError();
		closesocket(stub_connection_);
		WSACleanup();
		return false;
	}
	// Connect to server
	int connectionResult = connect(stub_connection_, (sockaddr*)&addr_, 
                                   sizeof(addr_));

	if (connectionResult == SOCKET_ERROR) {
        BOOST_LOG_TRIVIAL(error) << 
		"Client:: Connect: Cannot connect to server!" <<
        WSAGetLastError;
		closesocket(stub_connection_);
		WSACleanup();
		return false;
	}
    BOOST_LOG_TRIVIAL(info) << "Client::Connect(): Connection established!";
	return true;
}

// Clients public interface for sending a message
bool Client::SendMsg(std::string &message, std::string &msg_type) {
	mtx.lock(); // Thread Locks two step message function
	if (!SendMsgType(msg_type)) {
		return false;
	}
	int msg_len = message.size();

	if (!SendMsgLen(msg_len)) {
		return false;
	}
	if (!SendFullMsg(message, msg_len)) {
		return false;
	}
	mtx.unlock();
	return true;
}

// Function sends the message type
bool Client::SendMsgType(std::string &msg_type) {
	int msg_type_size = msg_type.size();
	if (!SendMsgLen(msg_type_size)) {
		return false;
	}

	if (!SendFullMsg(msg_type, msg_type_size)) {
		return false;
	}
	return true;
}

// Function sends the message length
bool Client::SendMsgLen(const int kMsgLength) {
	if (send(stub_connection_, (char*)&kMsgLength,
		sizeof(int), NULL) == SOCKET_ERROR) {
        BOOST_LOG_TRIVIAL(error) << "Client::SendMsgLen(): Connection lost: ";
		closesocket(stub_connection_);
		return false;
	}
	return true;
}

bool Client::SendFullMsg(std::string &message, int total_bytes) {
	int bytes_sent = 0;
	while (bytes_sent < total_bytes) {
		int bytes_returned = send(stub_connection_, 
            (char*)message.c_str() + bytes_sent, total_bytes - bytes_sent, NULL);
		if (bytes_returned == SOCKET_ERROR) {
			BOOST_LOG_TRIVIAL(error) << 
				"Lost Connection to Stub" << std::endl;
			closesocket(stub_connection_);
			return false;
		}
		bytes_sent += bytes_returned;
	}
	return true;
}

bool Client::CloseConnection() {
	if (closesocket(stub_connection_) == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAENOTSOCK) // happens when the socket has already been closed)
		return true; //return true since connection already closed
		BOOST_LOG_TRIVIAL(error) << "Failed to close the socket. Winsock Error: ";
		return false;
	}
	return true;
}