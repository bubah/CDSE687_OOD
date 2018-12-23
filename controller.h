///////////////////////////////////////////////////////////////////////////////
//        File: directory_management.cpp
// Description: Abstracts away the details of the file system
//    Language: Visual C++
//    Platform: MacBook Pro (Windows 10 Virtual Machine)
// Application: Project 3, Multi Node Map/Reduce Program
//      Author: Bubah Conteh, bconteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#ifndef CONTROLLER_H
#define CONTROLLER_H

#pragma once

#include <string>
#include <vector>
#include "client.h"

class Controller {
public:
	void MapMsgPhase(std::vector<std::string> &arguments);
	void ReduceMsgPhase(std::vector<std::string> &arguments);
	bool MapIsRunning(); // bool for if map clients are running
	bool ReduceIsRunning(); // bool for if reduce clients are running
	void MapClientHandler();
	void ReduceClientHandler();
private:
	int num_maps_running_{ 0 };
	bool maps_running_{ true };
	int num_reduce_running_{ 0 };
	bool reduce_running_{ true };
	std::vector<int> map_client_id_;
	std::string map_str_{ "MAP" };
	std::string reduce_str_{ "REDUCE" };
	std::vector<Client> list_stub_clients;
};

// Funtion partitions the temp file numbers each stub will 
// pass along to the reduce workers. Example: 34589_temp_1
// Function will assign _1 file to one stub and _2 to another
void TempFileId(std::vector<int> &ids, std::vector<int> 
	&part_reduce_workers) {
	ids[0] = 0; // initialize first index to zero
	int counter = 0; // counter varaible

	for (int index = 1; index < part_reduce_workers.size(); index++) {
		ids[index] = counter;
		for (int index_b = 0; index_b < part_reduce_workers[index - 1];
			index_b++) {
			ids[index]++;
			counter++;
		}
	}
}
#endif // CONTROLLER_H
