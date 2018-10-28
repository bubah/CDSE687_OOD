///////////////////////////////////////////////////////////////////
// Reduce.h - Reduces all data captured in input files from the 
//			  map process.
//
// Language: Visual C++
// Platform: MacBook Pro (Windows 10 Virtual Machine)
// Application: Project 1, Single Node Map/Reduce Program
// Author: Rob Hardisty
// Syracuse University, CSE 687 - Object Oriented Design
// rlhardis@syr.edu
//
///////////////////////////////////////////////////////////////////

#include "Reduce.h"
#include "FileManagement.h"
#include "Sort.h"
#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/list_of.hpp>

namespace ios = boost::iostreams;
namespace bm = boost::bimaps;

struct counter 
{
	counter() : c(0) {}
	counter& operator++() { ++c; return *this; }
	unsigned int operator++(int) { return c++; }
	operator const unsigned int() const { return c; }

private:
	unsigned int c;
};

// Our constructor is basically going to be initialized and perform all
// operations required to reduce the input data down.
Reduce::Reduce(string outputDir)
	:_dirOutput(outputDir)
{
}

// Constructor taking intermediate data and the FileManagement object
vector < std::pair<string, int> > Reduce::Reducer(string tmpData, FileManagement &fmObj)
{
	sumResults(tmpData);

	// Return the data as a vector of pairs
	return getOutputVector();
}

// Sum up the repeated tokens (regardless of case) and send to output vector
void Reduce::sumResults(string mapData)
{
	typedef bm::bimap <bm::unordered_set_of <std::string>, bm::list_of <counter> > word_counter;
	typedef boost::tokenizer<boost::char_separator<char> > text_tokenizer;
	
	// Feed the text into the container
	word_counter wc;
	text_tokenizer tok(mapData, boost::char_separator<char>("1 \t\n.,;:!?'\"-"));
	
	// Sum up the tokens
	for (text_tokenizer::const_iterator it = tok.begin(), it_end = tok.end(); it != it_end; ++it)
	{
		++wc.left[*it];
	}

	// Send the output to the vector private data member 
	for (word_counter::right_const_iterator wit = wc.right.begin(), wit_end = wc.right.end(); wit != wit_end; ++wit)
	{
		//std::cout << wit->second << ": " << wit->first << endl;
		_exportResults(wit->second, wit->first);
	}
}

// Getter for the output vector
vector < std::pair<string, int> > Reduce::getOutputVector()
{
	return _outputVector;
}

// Write out the results to the output folder
void Reduce::_exportResults(std::string key, int value)
{
	// Sort by key
	_outputVector.push_back( std::make_pair(key, value) );
}

void Reduce::writeSuccessFile(FileManagement &fmObj)
{
	// Create an empty file flagging the SUCCESS status
	fmObj.writeToOutputFile("SUCCESS", "");
}
