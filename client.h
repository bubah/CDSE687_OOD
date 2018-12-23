///////////////////////////////////////////////////////////////////////////////
//        File: client.h
// Description: Connects to the server for packet communications between the
//              controller and Map/Reduce processes and with the stub.
//    Language: Visual C++
//    Platform: MacBook Pro (Windows 10 Virtual Machine)
// Application: Project 3, Single Node Map/Reduce Program
//      Author: Rob Hardisty/Bubah Conteh, rlhardis@syr.edu/bconteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#ifndef CLIENT_H
#define CLIENT_H
#include <winsock2.h>
#include <string>

class Client {
public:
	Client(std::string ip, int port);
	bool Connect();
	bool SendMsg(std::string &message, std::string &msg_type);
	bool CloseConnection();
private:
	bool SendMsgLen(const int kMsgLength);
	bool SendFullMsg(std::string &message, int total_bytes);
	bool SendMsgType(std::string &msg_type);

private:
	SOCKET stub_connection_;//This client's connection to the server
	SOCKADDR_IN addr_; //Address to be binded to our Connection socket
	int sizeofaddr_ = sizeof(addr_); //Need sizeofaddr for the connect function
};
#endif // CLIENT_H
