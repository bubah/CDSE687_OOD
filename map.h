#ifndef MAP_H
#define MAP_H

///////////////////////////////////////////////////////////////////////////////
// Map.h - Interface for Map class ver 1.0
//														
// Language:    C++, Visual Studio 2017												
// Platform:    Microsoft Surface Pro 4, Windows 10									
// Application: Project 1, Single Node Map/Reduce Program							
// Author:      Bubah Conteh, Syracuse University CSE 687 - 
//				Object Oriented Design	
//              bconteh@syr.edu														
///////////////////////////////////////////////////////////////////////////////

#include <boost/tokenizer.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/log/trivial.hpp>
#include <vector>
#include <string>

namespace fs = boost::filesystem;

class MapInterface {
public:
	//Default Constructor
	MapInterface(size_t buffer = 0):bufferCap_{buffer}{}
	virtual ~MapInterface() {}

	// Mapper function
	virtual void Mapper(const std::string key, 
		const std::string value, std::function<void(std::string, std::string, size_t)>) = 0;

	// Returns beffer capacity
	size_t GetBufferCap() { return bufferCap_; }
	void SetBufferCap(size_t buffer) { bufferCap_ = buffer; }
private:
	size_t bufferCap_; // Buffer cap
};

#endif
