///////////////////////////////////////////////////////////////////////////////
//        File: reduce_process.cpp
// Description: Implementaton file for reduce_process 
//    Language: Visual C++
//    Platform: Windows 10 (visual studio 2017 Community)
// Application: Project 3, Multi-Node map reduce
//      Author: Bubah Conteh, BConteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#include <boost/thread/thread.hpp>
#include <boost/log/trivial.hpp>

#include <map>
#include <thread>

#include "client.h"
#include "combiner.h"
#include "reduce.h"
#include "reduce_process.h"

typedef boost::filesystem::path BoostPath;
typedef std::vector< std::pair<std::string, std::string> > VectorStrStr;
typedef std::map< std::string, std::string > MapStrStr;
typedef ReduceInterface*(*myFNPTR2)(std::string);

#define MILLISEC  1000

void WriteSuccessFile(FileManagement &fmobj, BoostPath output_dir) {
	fmobj.WriteToOutputFile("SUCCESS", "", output_dir);
}

std::string TempFileNameConfig(std::string map_id, int reduce_partition_number) {
	std::string temp = "temp";
	return map_id + "_" + temp + "_" + std::to_string(reduce_partition_number);
}

ReduceProcess::ReduceProcess() {}
void ReduceProcess::SpawnProcess() {}
std::vector<std::string> msgType = { "ID", "HeartBeat", "DONE" };
std::vector<std::string> msg = { "Im Alive", "Still Alive!", "Terminating" };
// spawn map process
int ReduceProcess::SpawnProcess(DirectoryManagement &dmobj, FileManagement& fmobj,
	const int kNumPartitions, std::vector<std::string> &input_files) {
	return 0;
}

int ReduceProcess::SpawnProcess(
	DirectoryManagement &dmobj,
	FileManagement &fmobj,
	const int kNumPartitions,
	const int kReducePartitionNum,
	std::vector<std::string> map_ids) {
	BOOST_LOG_TRIVIAL(info) << "Starting Reduce Phase";
	Client reduce_client(kLocalHostIP, kLocalHostPort);
	static std::function<void()> reduce_phase_lambda = [&]() {
		reduce_client.Connect();
		while (true) {
			if (!reduce_client.SendMsg(msg[1], msgType[1])) {
				break;
			}
			Sleep(1000);
		}
	};

	std::thread reduce_phase_thread(&ReduceProcess::ReduceClientThread, 
                                    std::ref(reduce_phase_lambda));
    reduce_phase_thread.detach();
	std::string dll_string = dmobj.GetDllDir().string();
	const char* text = dll_string.c_str();
	wchar_t wtext[100];
	size_t outsize;
	mbstowcs_s(&outsize, wtext, text, strlen(text) + 1); // Plus null
	LPWSTR ptr = wtext;
	HINSTANCE hInst = LoadLibrary(ptr);
	if (!hInst) {
		BOOST_LOG_TRIVIAL(error) << "Could not load the Reduce Library";
		return EXIT_FAILURE;
	}
	myFNPTR2 Reduce = (myFNPTR2)GetProcAddress(hInst, "CreateReduce");
	if (!Reduce) {
		BOOST_LOG_TRIVIAL(error) << "Could not locate CreateReduce...";
		return EXIT_FAILURE;
	}
	std::string map_data{ "" };
	for (int idx = 0; idx < map_ids.size(); idx++) {
		BOOST_LOG_TRIVIAL(info) << "Reading file: " << 
            TempFileNameConfig(map_ids[idx], kReducePartitionNum);
		std::string temp_map_data = fmobj.ReadWholeFile(
            TempFileNameConfig(map_ids[idx], kReducePartitionNum), 
            dmobj.GetTempDir());
		map_data += temp_map_data;
	}
	BOOST_LOG_TRIVIAL(info) << "ReduceProcess::ReduceProcess: Before Reduce "
        "DLL is called...";
	// Run the reduce process and write SUCCESS file when complete
	ReduceInterface* reduce_obj = Reduce(dmobj.GetOutputDir().string());
	// Convert the string data to a map
	Combiner cmb;
	MapStrStr temp_map;
	temp_map = cmb.Combine(map_data);
	// Reduce the sorted map data
	for (MapStrStr::const_iterator itr = temp_map.begin(); 
         itr != temp_map.end(); ++itr) {
		reduce_obj->Reducer(itr->first, itr->second);
	}
	MapStrStr reduced_map = reduce_obj->GetOutputMap();
	BOOST_LOG_TRIVIAL(info) << "ReduceProcess::ReduceProcess: Writing output "
        "file...";
	// Write the reduced/sorted map data
	fmobj.WriteToOutputFile(
		dmobj.GetOutputFilename(),
		reduced_map,
		dmobj.GetOutputDir());
	reduce_client.SendMsg(msg[2], msgType[2]);
	reduce_client.CloseConnection();
	BOOST_LOG_TRIVIAL(info) << "ReduceProcess::ReduceProcess: Exiting Reduce Process";

	return 0;
}

void ReduceProcess::ReduceClientThread(FNPTRVOID func) {
	func();
}
