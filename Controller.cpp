///////////////////////////////////////////////////////////////////////////////
//        File: controller.cpp
// Description: Delegates tasks to workers
//    Language: Visual C++
//    Platform: MacBook Pro (Windows 10 Virtual Machine)
// Application: Project 3, Multi Node Map/Reduce Program
//      Author: Bubah Conteh, bconteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////

// The contorller Delegates the task of kicking off map and reduce workers
// to the a number of stubs. Number of stubs is defined by the number of port
// numbers entered in to the command arguments.
// Port numbers must come after all the directory and number of map/reduce
// arguments. Also utilizes a server class to listen for messages from the
// map and reduce workers

// arg1 - inputDir
// arg2 - tempDir
// arg3 - outputDir
// arg4 - dllDir
// arg5 - #map
// arg6 - #reduce
// arg7 and onwards - port numbers

#pragma comment(lib, "ws2_32.lib")

#include <boost/thread/thread.hpp>
#include <WinSock2.h>
#include <WS2tcpip.h> 
#include <string>
#include <thread>

#include "client.h"
#include "controller.h"
#include "directory_management.h"
#include "file_aggregator.h"
#include "helper_functions.h"
#include "partition.h"
#include "server.h"

#define RD_LOCALHOST_PORT  54
#define MP_LOCALHOST_PORT  1111
#define LOCALHOST_IP  "127.0.0.1"

std::string spaceChar = " "; // Space variable used when forming concatenated strings

void Controller::MapMsgPhase(std::vector<std::string> &arguments) {
	int stub_idx_begin = 6; // stub ports begin at index 6
	int num_of_stubs = arguments.size() - stub_idx_begin; // number of stubs
	File_Aggregator file_aggr_obj; // Agrregates list of files per map process

	// create directory object
	DirectoryManagement dir_obj(arguments[0], arguments[1],
		arguments[2], arguments[3]);

	std::vector<std::string> vect_file_partitions
		= file_aggr_obj.Aggregate(dir_obj, num_of_stubs); // return vector of

	// Store port numbers to integer vector
	std::vector<int> list_of_ports(num_of_stubs);
	for (int port_index = 0; port_index < num_of_stubs; port_index++) {
		list_of_ports[port_index] =
			std::stoi(arguments[stub_idx_begin + port_index]);
	}

	// Partition map workers to stubs
	Partition part_obj;
	std::vector<int> part_map_workers =
		part_obj.PartitionMapWorkers(std::stoi(arguments[4]), num_of_stubs);

	// store string of stub messages to vector 
	std::vector<std::string> map_message(num_of_stubs);
	for (int arg_index = 0; arg_index < num_of_stubs; arg_index++) {
		map_message[arg_index] = arguments[0] + spaceChar +
			arguments[1] + spaceChar + arguments[2] + spaceChar +
			arguments[3] + spaceChar +
			std::to_string(part_map_workers[arg_index]) + spaceChar +
			arguments[5] + spaceChar + vect_file_partitions[arg_index];
	}

	// Create connection to stubs on each port in vector
	for (int client_index = 0; client_index < num_of_stubs; client_index++) {
		// Create Client sockets on IP "127.0.0.1"
		Client stub_client(LOCALHOST_IP, list_of_ports[client_index]);
		list_stub_clients.push_back(std::move(stub_client));
		list_stub_clients[client_index].Connect(); // connect vector of socks to ports

		// Send Message to Stubs to start Map procs
		list_stub_clients[client_index].SendMsg(map_str_, map_str_.size()); // Send message type
		list_stub_clients[client_index].SendMsg(map_message[client_index],
			map_message[client_index].size()); // Send message
	}

	num_maps_running_ = std::stoi(arguments[4]); // set total number of maps stubs will run
	while (MapIsRunning()) {} // While at least one map still runing loop here.
}

void Controller::ReduceMsgPhase(std::vector<std::string> &arguments) {
	int num_of_stubs = arguments.size() - 5; // number of stubs
	// Store port numbers to vector
	std::vector<int> list_of_ports(num_of_stubs);
	for (int index = 0; index < num_of_stubs; index++) {
		list_of_ports[index] = std::stoi(arguments[5 + index]);
	}

	// Partition reduce workers amongst stubs
	Partition part_obj;
	std::vector<int> part_reduce_workers =
		part_obj.PartitionMapWorkers(std::stoi(arguments[4]), num_of_stubs);
	
	// Create a vector of messages to pass to stubs running
	std::vector<int> file_part(part_reduce_workers.size());
	part_obj.TempFileId(file_part, part_reduce_workers);
	// Store messages to vector for the stubs
	std::vector<std::string> reduce_message(num_of_stubs);
	for (int arg_index = 0; arg_index < num_of_stubs; arg_index++) {
		reduce_message[arg_index] = arguments[0] + spaceChar +
			arguments[1] + spaceChar + arguments[2] + spaceChar +
			arguments[3] + spaceChar +
			std::to_string(part_reduce_workers[arg_index]) + spaceChar +
			std::to_string(file_part[arg_index]) + spaceChar +
			ConvertVecToStr(map_client_id_);
	}

	// Send corresponding message index to stubs
	for (int client_index = 0;
		client_index < num_of_stubs; client_index++) {

		// Send Messagetype "REDUCE"
		list_stub_clients[client_index].SendMsg(reduce_str_,
			reduce_str_.size());

		// Send REDUCE message
		list_stub_clients[client_index].SendMsg(reduce_message[client_index],
			reduce_message[client_index].size());
	}

	num_reduce_running_ = std::stoi(arguments[4]); // Set number of reduce procs that will run
	while (ReduceIsRunning()) {} // Loop here while reduce workers are still active
}

// Returns true if map workers are still active
bool Controller::MapIsRunning() {
	return maps_running_;
}

// Returns true if reduce workers are still active
bool Controller::ReduceIsRunning() {
	return reduce_running_;
}

//  Thread function to handle communication btwn control and map workers
void Controller::MapClientHandler() {
	Server mapServer(MP_LOCALHOST_PORT); // Create Socket on port 1111
	// Loop on socket to listen for messages from Map workers
	while (maps_running_) {
		mapServer.ListenForNewConnection();
		int num_connect = mapServer.GetNumOfConnections(); // Get number of workers connected
		// Lambda handle - function performs differtent tasks based
		// one the message type recieved from map workers.
		static FNPTR_INT_STR_STR map_client_lambda
			= [&](int id, std::string msgType, std::string msg) {
			// if message type is ID. Stores proc ID to vector
			if (msgType == "ID") {
				map_client_id_.push_back(std::stoi(msg));
			}
			else if (msgType == "HB") { // if msg type is HB print HeartBeat
				BOOST_LOG_TRIVIAL(info) <<
					"HeartBeat from map client ID: " << id;

			} else if (msgType == "DONE") { // If done decrement number of maps running
				BOOST_LOG_TRIVIAL(info) << "Mapper with ID " <<
					num_connect << " is complete!" << std::endl;
				num_maps_running_--; // Decrement maps
				BOOST_LOG_TRIVIAL(info) << "Number of map workers running" <<
					num_maps_running_;
				// If number of maps running is 0 set boolean var. to false
				if (num_maps_running_ == 0) {
					maps_running_ = false;
				}
			}
		};

		// Start thread on Server functino MapHandlerThread
		boost::thread map_client_thr(&Server::MapHandlerThread, num_connect,
			std::ref(map_client_lambda));
		mapServer.TotalConnectIncrementor(); // increment ID
		map_client_thr.detach();
	}
}

void Controller::ReduceClientHandler() {
	Server ReduceServer(RD_LOCALHOST_PORT);
	while (reduce_running_) {
		ReduceServer.ListenForNewConnection();
		int num_connect = ReduceServer.GetNumOfConnections();
		static FNPTR_INT_STR_STR lambda = [&](int id, std::string msgType,
			std::string msg) {
			// if message type is "HB" print to command
			if (msgType == "HB") {
				BOOST_LOG_TRIVIAL(info) <<
					"HeartBeat from Reduce client ID: " <<
					id;
			}
			else if (msgType == "DONE") { //  If Done, Decrement reducer count and print num of active reduce

				num_reduce_running_--;
				BOOST_LOG_TRIVIAL(info) << "Number of reduce running" <<
					num_reduce_running_;

				// If ruduce worker count is zero set bool var to false.
				if (num_reduce_running_ == 0) {
					reduce_running_ = false;
				}
			}
		};

		// Create thread on Server member function
		boost::thread Reduce_client_thr(&Server::ReduceHandlerThread,
			num_connect, std::ref(lambda));

		ReduceServer.TotalConnectIncrementor(); // increment number of reduce connections
		if (Reduce_client_thr.joinable()) {
			Reduce_client_thr.join();
		}
	}
}

int main(int argc, char *argv[]) {
	std::vector<std::string> map_args; // map phase arguments

	// Store cmd arguments to vector
	for (int index = 1; index < argc; index++) {
		map_args.push_back(argv[index]);
	}

	// Create a control object and run thread on its MapClientHandler function
	Controller controll_object;
	std::thread map_thread(&Controller::MapClientHandler, &controll_object);
	map_thread.detach();

	// Begin the phase for sending commands to stub to create map workers
	controll_object.MapMsgPhase(map_args);

	// store command line args to string vector
	std::vector<std::string> reduce_msg_args;
	for (int arg_index = 1; arg_index < argc; arg_index++) {
		if (arg_index != 5) {
			reduce_msg_args.push_back(argv[arg_index]);
		}
	}

	// Run a second thread on ReduceClientHandler function
	std::thread reduce_thread(&Controller::ReduceClientHandler,
		&controll_object);
	controll_object.ReduceMsgPhase(reduce_msg_args);

	reduce_thread.detach();

	// Write success file
	BoostPath output_dir = argv[3];
	FileManagement file_obj;
	WriteSuccessFile(file_obj, output_dir);
}