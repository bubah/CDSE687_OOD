///////////////////////////////////////////////////////////////////////////////
//        File: map_process.cpp
// Description: Implementaton file for map_process 
//    Language: Visual C++
//    Platform: Windows 10 (visual studio 2017 Community)
// Application: Project 3, Multi-Node map reduce
//      Author: Bubah Conteh, BConteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#include <boost/log/trivial.hpp>
#include <boost/thread/thread.hpp>

#include <chrono>
#include <mutex>

#include "client.h"
#include "helper_functions.h"
#include "map_process.h"
#include "../Map_Phase/Map.h"

#define LOCALHOST_PORT  1111
#define LOCALHOST_IP  "127.0.0.1"
#define MILLISEC  1000

typedef boost::filesystem::path BoostPath;
typedef boost::filesystem::ifstream BoostIFS;
typedef MapInterface*(*myFNPTR)(size_t); // define functon pointer
typedef std::vector < std::pair < std::string, std::string>> VectorStrStr;
typedef std::function< void(std::string, std::string, size_t) >
FnPtrStrStrSizeT; // define function pointer

void MapProcess::SpawnProcess() {};

std::vector<std::string> msgType = { "ID", "HB", "DONE" };
std::vector<std::string> msg = { "Im Alive", "Still Alive!", "Terminating" };

// This function holds code related to the map phase in mapReduce
// Function notifies the controller of its process id in its initial
// message. Then sends heartbeats to the controller on a dedicated thread
// When the map phase is complete it sends a message notfying the controller

int MapProcess::StartPhase(DirectoryManagement &dm, FileManagement& fm,
	const int num_partitions, std::vector<std::string> &input_files) {
	BOOST_LOG_TRIVIAL(info) << "Starting Map Phase";

	Client map_client(LOCALHOST_IP, LOCALHOST_PORT);
	std::string process_Id = std::to_string(GetCurrentProcessId());

	// Lambda captures client object and passed to thread
	static std::function<void()> map_phase_lambda = [&]() {
		map_client.Connect(); // Connect to controller socket

		// Send process ID to the controller
		map_client.SendMsg(process_Id, msgType[0]);

		// Loops through and sends heartbeats to the controller
		while (true) {
			// If message send returns an error break out of the loop.
			if (!map_client.SendMsg(msg[1], msgType[1])) {
					break;
			}
			Sleep(1000);
		}
	};

	// Create thread on MapClientthread function
	std::thread map_phase_thread(&MapProcess::MapClientThread,
	std::ref(map_phase_lambda));
	map_phase_thread.detach();

	std::string dll_string = dm.GetDllDir().string(); // store Dll path to string variable
	const char* text = dll_string.c_str(); // store dll string to char ptr
	wchar_t wtext[100];
	size_t outsize;
	mbstowcs_s(&outsize, wtext, text, strlen(text) + 1);
	LPWSTR ptr = wtext;
	HINSTANCE hInst = LoadLibrary(ptr); // load map Dll

	// If load error Log error to console and return exit failure
	if (!hInst) {
		BOOST_LOG_TRIVIAL(error) << "\nCould not load the Map Library";
		return EXIT_FAILURE;
	}

	// Resolve the function address
	myFNPTR Map = (myFNPTR)GetProcAddress(hInst, "CreateMap");

	// If error Log error to console and return exit failure
	if (!Map) {
		BOOST_LOG_TRIVIAL(info) << "\nCould not locate the createMap function";
		return EXIT_FAILURE;
	}

	// Run the map process
	MapInterface* map_obj = Map(100000);

	// Memory buffer passed to Map function
	static VectorStrStr *buffered_memory = new VectorStrStr();
	FnPtrStrStrSizeT fun = MakeLambda(dm, buffered_memory, num_partitions);
	int loop_counter = 0; // initialize count

	while (loop_counter < input_files.size()) { // loop until input files are read
		BOOST_LOG_TRIVIAL(info) << "Processing file: "
			<< input_files[loop_counter];

		// get input file name and store as path
		BoostPath input_path(input_files[loop_counter]);
		BoostIFS ifs{ input_path };

		// loop through file until reach end of file
		while (!ifs.eof()) {
			map_obj->Mapper(
			input_files[loop_counter],
			fm.ReadLineFromFile(input_files[loop_counter], &ifs),
			fun);
		}
		loop_counter++; // increment file loop_counter
	}

	// release remaining data in buffer to temporary file.
	EmptyBuffer(buffered_memory, 0, dm, num_partitions);

	map_client.SendMsg(msg[2], msgType[2]);
	map_client.CloseConnection();
	BOOST_LOG_TRIVIAL(info) << "Exiting Map Process";
	return 0;
}

void MapProcess::MapClientThread(FNPTRVOID func) {
	func();
}
