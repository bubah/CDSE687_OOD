#ifndef MAPREDUCE_H
#define MAPREDUCE_H

#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/log/trivial.hpp>
#include <boost/iostreams/stream.hpp>
#include <fstream>
#include <vector>

namespace fs = boost::filesystem;

class MapInterface {
public:

	//Default Constructor
	MapInterface(size_t buffer = 0):bufferCap{buffer}{}
	virtual ~MapInterface() {}

	// Mapper function
	virtual void Mapper(const std::string inputFileName, const std::string FileContent, 
		const std::string tmpFileName, std::string inputDir, std::string tempDir, std::string outputDir, std::string dll_dir,
		void(*FNPTR_EMIT)(std::string, std::string, std::string, size_t buffer,
		std::string, std::string, std::string, std::string, std::vector<std::pair<std::string, std::string>> *bufferMemory),
		std::vector<std::pair<std::string, std::string>> *bufferMemory)=0  ;

	// Returns beffer capacity
	int GetBufferCap() { return bufferCap; }
	void SetBufferCap(size_t buffer) { bufferCap = buffer; }
private:
	size_t bufferCap; // Buffer cap
};

#endif
