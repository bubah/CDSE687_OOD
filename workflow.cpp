///////////////////////////////////////////////////////////////////
// workflow.cpp - Ties together all of the MapReduce processes
//
// Language: Visual C++
// Platform: MacBook Pro (Windows 10 Virtual Machine)
// Application: Project 1, Single Node Map/Reduce Program
// Author: Rob Hardisty
// Syracuse University, CSE 687 - Object Oriented Design
// rlhardis@syr.edu
//
///////////////////////////////////////////////////////////////////

#include <Windows.h>
#include "filemanagement.h"
#include "directory_management.h"
#include "workflow.h"
#include "sort.h"
#include "C:/Users/conte/Documents/MapReduce/MapReduce/Map.h"
#include "C:/Users/conte/Documents/MapReduce/MapReduce/Reduce.h"
#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"
#include "boost/log/trivial.hpp"

typedef MapInterface*(*myFNPTR)(size_t);
typedef ReduceInterface*(*myFNPTR2)(std::string);
typedef std::vector < std::pair < std::string, std::string>> vector_pair_str;

size_t partitionFunction(size_t numberMap, size_t totalFileLines) {
	return ceil((double)totalFileLines / numberMap);
}

void EmptyBuffer(vector_pair_str *buffered_memory, size_t buffer, std::string filename,
	std::string input_dir, std::string temp_dir, std::string output_dir, std::string dll_dir) {
	if (buffered_memory->size() >= buffer) { // if buffer reaches cap write data to disk and clear buffer
		FileManagement fileObj(input_dir, temp_dir, output_dir, dll_dir);
		fileObj.WriteToTempFile(filename, *buffered_memory, temp_dir);
		buffered_memory->clear();
	}
}

// Funtion exports Key/Value pair from Map to buffer
void Emit(std::string key, std::string value, std::string filename, size_t buffer, std::string inputDir,
	std::string tempDir, std::string outputDir, std::string dll_dir, vector_pair_str *buffered_memory) {
	std::pair<std::string, std::string> key_value; // Declare a temp variable to store key/value pair
	key_value.first = key;
	key_value.second = value;
	buffered_memory->push_back(key_value); // push key/value pair to buffer in memmory
	EmptyBuffer(buffered_memory, buffer, filename, inputDir, tempDir, outputDir, dll_dir);

}

void WriteSuccessFile(FileManagement &fmobj, boost::filesystem::path outputDir) {
	fmobj.WriteToOutputFile("SUCCESS", "", outputDir);
}

Workflow::Workflow() {}

// Constructor taking all of the user udentified working directories
int Workflow::WorkflowMain(std::string input_dir, std::string temp_dir, 
	std::string output_dir, std::string dll_dir) {
	BOOST_LOG_TRIVIAL(info) << "Instantiating the Workflow object using class constructor" << "\n";
	// Declare an instance of the FileManagement class
	FileManagement fmobj(input_dir, temp_dir, output_dir, dll_dir);
	DirectoryManagement dmobj(input_dir, temp_dir, output_dir, dll_dir);

	int i = MapWorkFlow(dmobj, fmobj); // Run Map Phase

	//Sort data in temp file
	Sort<std::string> st(fmobj.ReadWholeFile(dmobj.GetTempFilename(), dmobj.GetTempDir()));
	st.SortData();
	std::vector<std::string> mystr = st.ExportSortedData();
	fmobj.WriteToTempFile(dmobj.GetTempFilename(), mystr, dmobj.GetTempDir());

	int j = ReduceWorkFlow(dmobj, fmobj); // Run Reduce Phase

	// Write the SUCCESS file
	WriteSuccessFile(fmobj, dmobj.GetOutputDir());

	return 0;
}

int Workflow::MapWorkFlow(DirectoryManagement &dm, FileManagement& fm) {
	std::string dll_string = dm.GetDllDir().string();
	const char* text = dll_string.c_str();
	wchar_t wtext[100];
	size_t outsize;
	mbstowcs_s(&outsize, wtext, text, strlen(text) + 1); // Plus null
	LPWSTR ptr = wtext;
	HINSTANCE hInst = LoadLibrary(ptr);

	if (!hInst) {
		BOOST_LOG_TRIVIAL(info) << "\nCould not load the Map Library";
		return EXIT_FAILURE;
	}

	//Resolve the function address
	myFNPTR Map = (myFNPTR)GetProcAddress(hInst, "CreateMap");
	if (!Map) {
		BOOST_LOG_TRIVIAL(info) << "\nCould not locate the createMap function";
		return EXIT_FAILURE;
	}

	////////////////////////////////////////////////////////////////////
	///////////////////////////////|   MAP
	////////////////////////////////////////////////////////////////////

	// Run the map process
	MapInterface* mp = Map(100000);

	static vector_pair_str *buffered_memory = new vector_pair_str(); // Memory buffer passed to Map function

	while ("-1" != dm.GetInputFilename()) {
		BOOST_LOG_TRIVIAL(info) << "Processing file: " << dm.GetInputFilename();
		std::string str{ "" };
		boost::filesystem::path inputPath(dm.GetInputFilename());
		boost::filesystem::ifstream ifs{ inputPath };

		while (!ifs.eof()) { // loop until reach end of file
			mp->Mapper(dm.GetInputFilename(), fm.ReadLineFromFile(dm.GetInputFilename(), ifs),
				dm.GetTempFilename(), dm.GetInputDir().string(), dm.GetTempDir().string(),
				dm.GetOutputDir().string(), dm.GetDllDir().string(), Emit, buffered_memory);
		}

		dm.IncrementInputFilePointer(); // increment file pointer
	}

	// release remaining data in buffer to file.
	EmptyBuffer(buffered_memory, 0, dm.GetTempFilename(), dm.GetInputDir().string(),
		dm.GetTempDir().string(), dm.GetOutputDir().string(), dm.GetDllDir().string());
	return 0;
}

int Workflow::ReduceWorkFlow(DirectoryManagement &dm, FileManagement& fm) {
	std::string dll_string = dm.GetDllDir().string();
	const char* text = dll_string.c_str();
	wchar_t wtext[100];
	size_t outsize;
	mbstowcs_s(&outsize, wtext, text, strlen(text) + 1); // Plus null
	LPWSTR ptr = wtext;
	HINSTANCE hInst = LoadLibrary(ptr);


	std::string mapData = fm.ReadWholeFile(dm.GetTempFilename(), dm.GetTempDir());

	////////////////////////////////////////////////////////////////////
	///////////////////////////////|   REDUCE
	////////////////////////////////////////////////////////////////////
	myFNPTR2 Reduce = (myFNPTR2)GetProcAddress(hInst, "CreateReduce");

	if (!Reduce)
	{
		std::cout << "\nCould not locate the create Reduce function";
		return EXIT_FAILURE;
	}

	// Run the reduce process and write SUCCESS file when complete
	ReduceInterface* rd = Reduce(dm.GetOutputDir().string());

	// Reduce the sorted map data
	std::vector< std::pair<std::string, std::string> > vectorData = rd->Reducer(mapData);

	// Write the reduced/sorted map data
	fm.WriteToOutputFile(dm.GetOutputFilename(), vectorData, dm.GetOutputDir());
	return 0;
}
