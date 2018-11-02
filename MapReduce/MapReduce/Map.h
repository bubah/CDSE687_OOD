////////////////////////////////////////////////////////////////////////////////
// Map.h - tokenizes string of raw data into unique words and exports 
//			intermediate key/value pair.															
// Language:    C++, Visual Studio 2017												
// Platform:    Microsoft Surface Pro 4, Windows 10									
// Application: Project 1, Single Node Map/Reduce Program							
// Author:      Bubah Conteh, Syracuse University CSE 687 - Object Oriented Design	
//              bconteh@syr.edu														
////////////////////////////////////////////////////////////////////////////////

#ifndef MAP_H
#define MAP_H

#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>  
#include <boost/log/trivial.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "FileManagement.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
namespace fs = boost::filesystem;

class Map
{
public:
	// Default Constructor
	Map(const size_t buffer = 100000);

	

	// Mapper function calls prive method 'tokenizer'
	void mapper(const string inputFileName, const string FileContent, const string tmpFileName, FileManagement &);

	// Export function call prive 'emmitter' function.
	void exportt(const string tmpFileName, FileManagement &);

private:

	// Supress white spaces, capitals & punctuation from input data
	void tokenizer(const string fileContent); 

	// Exports key/Value to interm file
	void emmitter(const string key, const string value, const string tmpFileName, FileManagement &); 

	// Stores the size of this class's vector 
	size_t wordsSize;

	// Buffer capacity
	size_t buffer; 

	// Stores input data recieved from input file
	vector<string> words;
};

#endif // !MAP_H