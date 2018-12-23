///////////////////////////////////////////////////////////////////////////////
//        File: reduce.h
// Description: Header file for the reduce class.
//    Language: Visual C++
//    Platform: Windows 10 (visual studio 2017 Community)
// Application: Project 3, Multi-Node map reduce
//      Author: Rob Hardisty, rlhardis@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#include <boost/log/trivial.hpp>
#include <boost/algorithm/string.hpp>

#include <iostream>
#include <map>

#include "reduce.h"

#ifdef MAPREDUCE_EXPORTS
#define MAPREDUCE_API __declspec(dllexport)
#endif

class MAPREDUCE_API Reduce : public ReduceInterface {
public:
	Reduce();
	Reduce(std::string);
	~Reduce();
    void Reducer( const std::string &key, const std::string &value );
	// Getter for the output vector data
    MapStrStr GetOutputMap();
private:
	// Saves data to the output vector private data member
	void ExportResults(std::string key, std::string value);
	// Aggregates the data and sums up repeated keys
	int SumResults(const std::string &value);
    MapStrStr output_map_;
	// Contains the output directory location
	std::string dir_output_;
};

extern "C" MAPREDUCE_API ReduceInterface* CreateReduce(std::string str) {
	return new Reduce(str);
}

Reduce::Reduce() { 
	BOOST_LOG_TRIVIAL(info) << "Reduce::Reduce()..."; 
}

Reduce::Reduce(std::string output_dir) :dir_output_(output_dir) { 
	BOOST_LOG_TRIVIAL(info) << "Reduce::Reduce(string)..."; 
}

Reduce::~Reduce() {
    BOOST_LOG_TRIVIAL( info ) << "~Reduce::Reduce()...";
}

void Reduce::Reducer( const std::string &key, const std::string &value ) {
    int results = 0;
    results = SumResults( value );
    ExportResults( key, std::to_string(results) );
}

// Sum up the repeated tokens (regardless of case) and send to output vector
int Reduce::SumResults( const std::string &value ) {
    // Sum the results
    int sum_of_elems = 0;
    std::vector<std::string> results; 
    boost::split( results, value, [] ( char c ) {return c == ','; } );
    for (std::string &n : results ) { 
		sum_of_elems += std::stoi( n );
	}
    return sum_of_elems;
}

// Getter for the output vector
MapStrStr Reduce::GetOutputMap() {
	BOOST_LOG_TRIVIAL(info) << "Reduce::GetOutputMap called...";
	return output_map_;
}

// Write out the results to the output folder
void Reduce::ExportResults(std::string key, std::string value) {
    output_map_.insert( std::pair<std::string, std::string>( key, value ) );
}
