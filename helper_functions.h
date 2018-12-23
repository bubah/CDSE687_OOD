///////////////////////////////////////////////////////////////////////////////
//        File: helper_functions.cpp
// Description: Utility functions/Lambda used in map_process.cpp
//    Language: Visual C++
//    Platform: Windows 10 (visual studio 2017 Community)
// Application: Project 3, Multi-Node map reduce
//      Author: Bubah Conteh, BConteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#ifndef HELPER_FUNCTION_H
#define HELPER_FUNCTION_H

#include <vector>
#include <string>

#include "directory_management.h"
#include "filemanagement.h"

typedef std::vector < std::pair < std::string, std::string>> vector_pair_str;
typedef std::function<void(std::string, std::string, size_t)>
functionPtr_str_str_size_t; // define function pointer

// Function released data in buffer to temp file if buffer reaches cap
static void EmptyBuffer(vector_pair_str *buffered_memory, size_t buffer,
	DirectoryManagement dm, int numOfPartitions) {
	if (buffer < 0) {
		buffer = 0;
	} // if buffer is less than zero set buffer to default size

	// if buffer reaches cap write data to disk and clear buffer
	if (buffered_memory->size() > buffer) {

		FileManagement fileObj; // Create file object
		std::string filename = dm.GetTempFilename();
		std::string temp_dir = dm.GetTempDir().string();

		fileObj.WriteToTempFile(filename, *buffered_memory, temp_dir,
			numOfPartitions); // write buffered data to temp file

		buffered_memory->clear(); // clear buffer memory
	}
}

// Funtion exports Key/Value pair from Map to buffer
void Emit(const std::string &key, const std::string &value,
	DirectoryManagement dm, const size_t &buffer,
	vector_pair_str *buffered_memory, const int &numOfPartitions) {

	// Declare a temp variable to store key/value pair
	std::pair<std::string, std::string> key_value;

	key_value.first = key;

	key_value.second = value;

	// push key/value pair to buffer in memmory
	buffered_memory->push_back(key_value);

	// call empty buffer function
	EmptyBuffer(buffered_memory, buffer, dm, numOfPartitions);
}

// function returns a lambda
functionPtr_str_str_size_t MakeLambda(DirectoryManagement dm,
	vector_pair_str *buffered_memory, int numOfPartitions) {

	return [=](std::string key, std::string value, size_t buffer) {
		Emit(key, value, dm, buffer, buffered_memory, numOfPartitions);
	};
}

void WriteSuccessFile(FileManagement &fmobj, BoostPath &output_dir) {
	fmobj.WriteToOutputFile("SUCCESS", "", output_dir);
}

// Function converts a vector of integers to one string delimited by spaces
std::string ConvertVecToStr(std::vector<int> &vect) {
	std::string temp_string;
	for (int vec_index = 0; vec_index < vect.size(); vec_index++) {
		temp_string += std::to_string(vect[vec_index]) + " ";
	}
	return temp_string;
}

#endif // HELPER_FUNCTION_H
