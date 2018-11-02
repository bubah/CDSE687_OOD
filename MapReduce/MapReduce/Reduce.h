///////////////////////////////////////////////////////////////////
// Syracuse University, CSE 687 - Object Oriented Design
// Reduce.h file for Project 1
//
// LANGUAGE:	Visual C++
// PLATFORM:	MacBook Pro (Windows 10 Virtual Machine)
// APPLICATION:	Project 1, Single Node Map/Reduce Program
// AUTHOR:		Rob Hardisty
// EMAIL:		rlhardis@syr.edu
// DESCRIPTION:	Reads in datafiles from a temp directory and 
//				reduces down the tokenized data
//
///////////////////////////////////////////////////////////////////

#ifndef REDUCE_H
#define REDUCE_H

#include "FileManagement.h"
#include <iostream>
#include <string>
#include <utility>
#include <boost/log/trivial.hpp>

class Reduce
{
public:
	Reduce(std::string);

	// Main function that reduces the data passed from Map
	vector< std::pair<string, int> > Reducer(std::string, FileManagement &);

	// Aggregates the data and sums up repeated keys
	void sumResults(std::string);

	// Getter for the output vector data
	vector< std::pair<string, int> > getOutputVector();

	// Write an empty file flagging SUCCESS
	void writeSuccessFile(FileManagement &);

private:

	// Saves data to the output vector private data member
	void _exportResults(std::string, int);

	// Stores the aggregated data from _exportResults()
	vector< std::pair<std::string, int> > _outputVector;

	// Contains the output directory location
	std::string _dirOutput;

	// Contains the temporary directory location
	std::string _dirTemp;

};


#endif