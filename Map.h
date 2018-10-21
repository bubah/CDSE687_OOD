#ifndef MAP_H
#define MAP_H

//////////////////////////////////////////////////////////////////////////////////////
// Map.h - tokenizes string of raw data into unique words and emits intermediate	//
//			key/data pair.															//
// Language:    C++, Visual Studio 2017												//
// Platform:    Microsoft Surface Pro 4, Windows 10									//
// Application: Project 1, Single Node Map/Reduce Program							//
// Author:      Bubah Conteh, Syracuse University CSE 687 - Object Oriented Design	//
//              bconteh@syr.edu														//
//////////////////////////////////////////////////////////////////////////////////////

#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
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
	Map(); //Default Constructor
	void mapper(string inputFileName, string FileContent, string tmpFileName, FileManagement &); 

private:
	void tokenizer(string fileContent); //extracts words from input files
	void emmitter(string key, string value, string tmpFileName, FileManagement &); //exports key/Value to interm file
	size_t wordsSize; // buffer size
	vector<string> words;  //buffer to store tokenized words
};

#endif // !MAP_H

