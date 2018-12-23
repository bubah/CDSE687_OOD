#ifndef SERVER_H
#define SERVER_H

#pragma once
#include <boost/log/trivial.hpp>

#include <string>
#include <vector>
#include <functional>

typedef std::function<void(int id, std::string, std::string)>
FNPTR_INT_STR_STR;

class Server {
public:
	Server(int port, bool broadcastPublically = false);
	bool ListenForNewConnection();
	bool RecvMessage(int iD, std::string &message);
	bool RecvMessageType(int iD, int &msgType);
	static void MapHandlerThread(int iD, FNPTR_INT_STR_STR func);
	static void ReduceHandlerThread(int iD, FNPTR_INT_STR_STR func);
	void TotalConnectIncrementor();
	int GetNumOfConnections();
	void SetNumMapsRunning(int num);
	void SetNumReduceRunning(int num);
	bool MapIsRunning();
	bool ReduceIsRunning();
private:
	bool RecvMessageLen(int iD, int &msg_length);
	bool RecvFullMessage(int iD, std::string &message, int total_bytes);

private:
	SOCKET map_sockets_[100];
	int total_map_connections_ = 0;
	std::vector<int> map_ids_;
	int num_maps_run_{ 0 };
	int num_reduce_run_{ 0 };
	bool maps_running_;
	bool red_running_;
	SOCKADDR_IN addr_; //Address that we will bind our listening socket to
	int addrlen_ = sizeof(addr_);
	SOCKET sListen_;
};

static Server * serverptr;

#endif // SERVER_H
