///////////////////////////////////////////////////////////////////
// Syracuse University, CSE 687 - Object Oriented Design
// Reduce.h file for Proj 2.0
//
// LANGUAGE:	Visual C++
// PLATFORM:	MacBook Pro (Windows 10 Virtual Machine)
// APPLICATION:	Project 1, Single Node Map/Reduce Program
// AUTHOR:		Rob Hardisty
// EMAIL:		rlhardis@syr.edu
// DESCRIPTION:	Reads in datafiles from a temp directory and 
//				reduces down the tokenized data
///////////////////////////////////////////////////////////////////
#ifndef REDUCE_H
#define REDUCE_H

#include <string>
#include <vector>
#include <iostream>

typedef std::map< std::string, std::string > MapStrStr;

class ReduceInterface {
public:
	ReduceInterface() {}
	virtual ~ReduceInterface() {}
	// Main function that reduces the data passed from Map
	virtual void Reducer( const std::string &key, const std::string &value ) = 0;
    virtual MapStrStr GetOutputMap() = 0;
};
#endif
