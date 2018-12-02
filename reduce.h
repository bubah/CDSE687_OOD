#ifndef WORDCOUNTREDUCE_H
#define WORDCOUNTREDUCE_H

#include <iostream>
#include <string>
#include "FileManagement.h"
#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/log/trivial.hpp>
#include <boost/dll.hpp>
#include <boost/iostreams/stream.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/list_of.hpp>

class ReduceInterface {
public:
	ReduceInterface() {}
	virtual ~ReduceInterface() {}

	// Main function that reduces the data passed from Map
	virtual std::vector< std::pair<std::string, std::string> > Reducer(std::string) = 0;

	// Aggregates the data and sums up repeated keys
	virtual void SumResults(std::string) = 0;

	// Getter for the output vector data
	virtual std::vector< std::pair<std::string, std::string> > GetOutputVector() = 0;
};

#endif
