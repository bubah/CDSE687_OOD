#include <string>
#include <vector>
#include <iostream>
#include "file_management.h"

typedef std::vector < std::pair < std::string, std::string>> vectorPairStr;

void EmptyBuffer(vectorPairStr *bufferedMemory, size_t buffer, std::string tempFileName, 
	std::string inputDir, std::string tempDir, std::string outputDir) {
	if (bufferedMemory->size() >= buffer) { // if buffer reaches cap write data to disk and clear buffer
		FileManagement fileObj(inputDir, tempDir, outputDir);
		fileObj.WriteToTmpFile(tempFileName, *bufferedMemory);
		bufferedMemory->clear();
	}
}

void Emit(std::string key, std::string value, std::string tempFileName, size_t buffer, 
	std::string inputDir, std::string tempDir, std::string outputDir, vectorPairStr *bufferedMemory) {
	std::cout << "Now running function Emit()" << std::endl;

	std::pair<std::string, std::string> keyValue; // Declare a temp variable to store key/value pair
	keyValue.first = key;
	keyValue.second = value;
	bufferedMemory->push_back(keyValue); // push key/value pair to buffer in memmory
	EmptyBuffer(bufferedMemory, buffer, tempFileName, inputDir, tempDir, outputDir);
}

void WriteSuccessFile(std::string outputFileName, std::string inputDir, std::string tempDir, std::string outputDir){
	FileManagement fileObj(inputDir, tempDir, outputDir);
	fileObj.WriteToOutputFile("SUCCESS", "");
}
