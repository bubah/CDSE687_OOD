////////////////////////////////////////////////////////////////////////////////
// Mapp.cpp -	Tokenizes in the input data in preparation for the reduce 
//				process	ver 1.0																			
// Language:    C++, Visual Studio 2017										
// Platform:    Microsoft Surface Pro 4, Windows 10								
// Application: Project 1, Single Node Map/Reduce Program							
// Author:      Bubah Conteh 
//				Syracuse University CSE 687 - Object Oriented Design
//              bconteh@syr.edu														
////////////////////////////////////////////////////////////////////////////////

#include "Map.h"
#include "FileManagement.h"
#include "Sort.h"

Map::Map(size_t bufferSize) :wordsSize{ 0 }, buffer{bufferSize}{ BOOST_LOG_TRIVIAL(info) << "Instantiating a Map object using default constructor" << "\n"; }

// Main processing component of the Map class
void Map::mapper(const string inputFileName, const string FileContent, 
				const string tmpFileName, FileManagement &fileObj) 
{
	BOOST_LOG_TRIVIAL(info) << "Now running Map Class public method mapper(string, string)" << "\n";
	tokenizer(FileContent);

	// export data if buffer reaches user defined cap.
	if (wordsSize >= buffer) {
		exportt(tmpFileName, fileObj);
	}
}


// Breaks apart the input data into pre-defined tokens, ignoring case
void Map::tokenizer(const string FileContent)
{
	BOOST_LOG_TRIVIAL(info) << "Now running Map Class private method tokenizer(string)" << "\n";
	typedef boost::tokenizer<boost::char_separator<char>> tokenizer; 
	boost::char_separator<char> sep{ "	,.`~@#$%^&*-_+=(){}[]<>\/|?':;! " }; // characters to disregard/supress
	tokenizer tok{ FileContent, sep };
	for (auto t : tok) {
		boost::algorithm::to_lower(t); // set words to lower case
		this->words.push_back(t);  // push word to back of vector
	}

	wordsSize = words.size();
}


// Main export function, sorts data before calling private emitter func.
void Map::exportt(const string tmpFileName, FileManagement &fileObj)
{
	BOOST_LOG_TRIVIAL(info) << "Now running Map Class public method exportt(string, FileManagement&)" << "\n";

	// If buffer is empty return
	if (wordsSize == 0) {
		return;
	}

	Sort st(words);
	st.SortData();
	vector<string> tempVec = st.exportSortedData(); 
	for (string word : tempVec) {
		emmitter(word, "1", tmpFileName, fileObj);
	}

	words.clear();
	wordsSize = words.size();
}


// Fucntion formats key/value pair before writing to temp file
void Map::emmitter(const string key, const string value, 
					const string tmpFileName, FileManagement &fileObj)
{
	const string keyValueParse = key + "," + value;
	fileObj.writeToTmpFile(tmpFileName, keyValueParse); // write key/value to temp file
}

