///////////////////////////////////////////////////////////////////////////////
//        File: start_process.cpp
// Description: Spawns off Map and Reduce Processes
//    Language: Visual C++
//    Platform: Windows 10 (visual studio 2017 Community)
// Application: Project 3, Multi-Node map reduce
//      Author: Bubah Conteh, BConteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////

#include "boost/log/trivial.hpp"
#include <boost/tokenizer.hpp>
#include <WinSock2.h>
#include "directory_management.h"
#include "file_aggregator.h"
#include "start_process.h"

typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
std::string spaceChar = " ";

void StartProcess::StartMap(std::string &arguments) {
	std::vector<std::string> controller_args;
	boost::char_separator<char> sep{ " " };
	tokenizer tok{ arguments, sep };
	for (std::string itr : tok) {
		controller_args.push_back(itr);
	}

	wchar_t map_wtext[10000];
	size_t map_outsize;
	std::vector<HANDLE> map_hProcess(std::stoi(controller_args[4]));  //process handle
	std::vector<HANDLE> map_hThread(std::stoi(controller_args[4]));		//thread handle
	std::vector<STARTUPINFO> map_si(std::stoi(controller_args[4]));
	std::vector<PROCESS_INFORMATION> map_pi(std::stoi(controller_args[4]));
	std::vector<DWORD> map_dwProcessId(std::stoi(controller_args[4]), 0);
	std::vector<DWORD> map_dwThreadId(std::stoi(controller_args[4]), 0);

	for (int map_index = 0; map_index <
		std::stoi(controller_args[4]); map_index++) {
		ZeroMemory(&map_si[map_index], sizeof(map_si[map_index]));
		ZeroMemory(&map_pi[map_index], sizeof(map_pi[map_index]));
	}

	std::string map_proc_ids; // store string of map process IDs

	std::vector < std::string> file_names(controller_args.size() - 6);
	for (int index = 0; index < controller_args.size() - 6; index++) {
		file_names[index] = controller_args[6 + index];
	}

	File_Aggregator file_obj;
	std::vector<std::string> vect_file_partitions =
		file_obj.Aggregate(file_names, std::stoi(controller_args[4]));

	BOOL create_map_process = NULL; // boolean variable to hold process return value

	// create some numbers of map processes specified by command line input
	for (int proc_num = 0; proc_num < 
		std::stoi(controller_args[4]); proc_num++) {
		// create string of cmd line args for ea. map process
		std::string map_proc_arguments = controller_args[0] + " "
			+ controller_args[1] + spaceChar + controller_args[2] + 
			spaceChar + controller_args[3] + spaceChar +
			controller_args[5] + spaceChar +
			vect_file_partitions[proc_num];

		const char* map_text = map_proc_arguments.c_str(); // store arguments to char ptr
		mbstowcs_s(&map_outsize, map_wtext, map_text, strlen(map_text) + 1); // Plus null
		LPTSTR  map_commandLine = map_wtext; // assign arg list to process command line param

		// Create map process
		create_map_process = CreateProcess(
			L"C:\\Map_Phase.exe",
			map_commandLine, NULL, NULL, FALSE, 0, NULL, NULL,
			&map_si[proc_num], &map_pi[proc_num]);

		//  Log error if proccess fails to create
		if (create_map_process == FALSE) {
			BOOST_LOG_TRIVIAL(error) << "Create Map Process Failed!";
		}

		// concatenate map process ids to string
		map_proc_ids += std::to_string(map_pi[proc_num].dwProcessId) + " ";

		BOOST_LOG_TRIVIAL(info) << "Create Map Process Success";
		BOOST_LOG_TRIVIAL(info) << "Process ID -> "
			<< map_pi[proc_num].dwProcessId;
		BOOST_LOG_TRIVIAL(info) << "Thread ID -> "
			<< map_pi[proc_num].dwThreadId;
		BOOST_LOG_TRIVIAL(info) << "GetProcessID -> "
			<< GetProcessId(map_pi[proc_num].hProcess);
		BOOST_LOG_TRIVIAL(info) << "GetThreadID - > "
			<< GetThreadId(map_pi[proc_num].hThread);
	}

	// wait for all map processes to complete
	for (int proc_num = 0; proc_num < std::stoi(controller_args[4]);
		proc_num++) {
		WaitForSingleObject(map_pi[proc_num].hProcess, INFINITE);
		CloseHandle(map_pi[proc_num].hThread);
		CloseHandle(map_pi[proc_num].hProcess);
	}
}

void StartProcess::StartReduce(std::string &arguments) {
	std::vector<std::string> controller_args;
	boost::char_separator<char> sep{ " " };
	tokenizer tok{ arguments, sep };
	for (std::string itr : tok) {
		controller_args.push_back(itr);
	}
	std::string map_proc_ids;
	int num_ids = controller_args.size() - 6;
	for (int index = 0; index < num_ids; index++) {
		map_proc_ids += controller_args[6 + index] + " ";
	}

	std::string temp_file_part = controller_args[5];

	wchar_t reduce_wtext[10000];
	size_t reduce_outsize;

	std::vector<HANDLE> reduce_hProcess(std::stoi(controller_args[5]));  //process handle
	std::vector<HANDLE> reduce_hThread(std::stoi(controller_args[4]));		//thread handle
	std::vector<STARTUPINFO> reduce_si(std::stoi(controller_args[4]));
	std::vector<PROCESS_INFORMATION> reduce_pi(std::stoi(controller_args[4]));
	std::vector<DWORD> reduce_dwProcessId(std::stoi(controller_args[4]), 0);
	std::vector<DWORD> reduce_dwThreadId(std::stoi(controller_args[4]), 0);

	BOOL create_reduce_process = NULL; // boolean variable to hold process return value

	std::string number_reduceProc_to_str = 
		std::to_string(std::stoi(controller_args[4]));

	// create some numbers of reduce processes specified by command line input
	for (size_t proc_num = 0; proc_num < std::stoi(controller_args[4]);
		proc_num++) {
		// create string of cmd line args for reduce process
		std::string reduceProc_arguments = controller_args[0] 
			+ " " + controller_args[1] + " " + controller_args[2] 
			+ " " + controller_args[3] + " " + 
			number_reduceProc_to_str + " " +
			std::to_string(proc_num + std::stoi(temp_file_part) + 1) +
			" " + map_proc_ids;

		const char* r_text = reduceProc_arguments.c_str();
		mbstowcs_s(&reduce_outsize, reduce_wtext, r_text, strlen(r_text) + 1); // Plus null
		LPTSTR  reduce_commandLine = reduce_wtext; // assign arg list to command line param

		create_reduce_process = CreateProcess(
			L"C:\\Reduce_Process.exe",
			reduce_commandLine, NULL, NULL, FALSE, 0, NULL, NULL,
			&reduce_si[proc_num], &reduce_pi[proc_num]);

		//  Log error if proccess fails
		if (create_reduce_process == FALSE) {
			BOOST_LOG_TRIVIAL(error) << "Create Reduce Process Failed!";
		}

		BOOST_LOG_TRIVIAL(info) << "Create Reduce Process Success";
		BOOST_LOG_TRIVIAL(info) << "Process ID -> " <<
			reduce_pi[proc_num].dwProcessId;
		BOOST_LOG_TRIVIAL(info) << "Thread ID -> " <<
			reduce_pi[proc_num].dwThreadId;
		BOOST_LOG_TRIVIAL(info) << "GetProcessID -> " <<
			GetProcessId(reduce_pi[proc_num].hProcess);
		BOOST_LOG_TRIVIAL(info) << "GetThreadID - > "
			<< GetThreadId(reduce_pi[proc_num].hThread);
	}

	// wait for all reduce processes to complete
	for (int proc_num = 0; proc_num < std::stoi(controller_args[4]);
		proc_num++) {
		WaitForSingleObject(reduce_pi[proc_num].hProcess, INFINITE);

		// close reduce process handles
		CloseHandle(reduce_pi[proc_num].hThread);
		CloseHandle(reduce_pi[proc_num].hProcess);
		BOOST_LOG_TRIVIAL(info) << "closing reduce handle";
	}
}
