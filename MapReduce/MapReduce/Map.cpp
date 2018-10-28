//////////////////////////////////////////////////////////////////////////////////////
// Mapp.cpp -	Tokenizes in the input data in preparation for the reduce process	//
// ver 1.0																			//
// Language:    C++, Visual Studio 2017												//
// Platform:    Microsoft Surface Pro 4, Windows 10									//
// Application: Project 1, Single Node Map/Reduce Program							//
// Author:      Bubah Conteh, Syracuse University CSE 687 - Object Oriented Design	//
//              bconteh@syr.edu														//
//////////////////////////////////////////////////////////////////////////////////////

#include "Map.h"
#include "FileManagement.h"

Map::Map() :wordsSize{ 0 }, wordStr{ "" } {}

// Main processing component of the Map class
void Map::mapper(const string inputFileName, const string FileContent, const string tmpFileName, FileManagement &fileObj) {
	tokenizer(FileContent);
	
	for (string word : words) {
		emmitter(word, "1", tmpFileName, fileObj);
	}

	words.clear(); // Clears Map Data member 'words'
	wordsSize = words.size(); //set size to current size
}

// Breaks apart the input data into pre-defined tokens, ignoring case
void Map::tokenizer(const string FileContent)
{
	typedef boost::tokenizer<boost::char_separator<char>> tokenizer; 
	boost::char_separator<char> sep{ "	,.`~@#$%^&*-_+=(){}[]<>\/|?':;! " }; // characters to disregard/supress
	tokenizer tok{ FileContent, sep };
	for (auto t : tok) {
		boost::algorithm::to_lower(t); // set words to lower case
		this->words.push_back(t);  // push word to back of vector
	}
}

// Send the data to the temporary file/folder
void Map::emmitter(const string key, const string value, const string tmpFileName, FileManagement &fileObj)
{
	const string keyValueParse = key + "," + value;
	fileObj.writeToTmpFile(tmpFileName, keyValueParse); // write key/value to temp file
}