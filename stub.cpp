///////////////////////////////////////////////////////////////////////////////
//        File: stub.cpp
// Description: Recieves messages from the controller
//				and Spawns off Map and Reduce processes 
//    Language: Visual C++
//    Platform: Windows 10 (visual studio 2017 Community)
// Application: Project 3, Multi-Node map reduce
//      Author: Bubah Conteh, BConteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////

#include <winsock2.h>     // Windows sockets, ver 2
#include <WS2tcpip.h>     // support for IPv6 and other things
#include <string>
#include <vector>

#include "stub_server.h"
#include "start_process.h"

#define LOCALHOST_PORT  54000 // Must hard code a unique port for ea. stub running

// Main function connects socket to port 54000 to listen in for 
// messages from the controller. When Stub recieve message it interprets the message
// and spawns off a Map or Reduce process

int main() {
	Server myServer(LOCALHOST_PORT); // Connect socket to port to 54000
	myServer.ListenForNewConnection(); // Listen for connection from Contorller

	StartProcess start_proc; // Instantiate process object

	// Loops and continue to Wait for messages from controller and execute. 
	while (true) {
		std::string message; // string to store actual instructoins
		std::string messageType; // string to determine which process to spawn

		// recieve process name from controller. If fail to recieve break from loop
		if (!myServer.RecvMessage(messageType)) {
			break;
		}

		// recieve instructions from controller. If fail to recieve break from loop
		if (!myServer.RecvMessage(message)) {
			break;
		}

		// if message type is "Map" spawn a map
		if (messageType == "MAP") {
			start_proc.StartMap(message);
		}
		else if (messageType == "REDUCE") { // else if message type is "Reduce" Spawn a reduce
			start_proc.StartReduce(message);
		}
		else { // else cout unrecongnized message and break
			BOOST_LOG_TRIVIAL(error) << "unrecongnized message " << message;
			break;
		}
	}
	BOOST_LOG_TRIVIAL(info) << "Lost Connection to Controller";
	return 0;
}
