#include "Map.h"
#include "FileManagement.h"

Map::Map() :wordsSize{ 0 } {}

void Map::mapper(string inputFileName, string FileContent, string tmpFileName, FileManagement &fileObj) {
	tokenizer(FileContent);
	for (string word : words) {
		emmitter(word, "1", tmpFileName, fileObj);
	}
}

void Map::tokenizer(string FileContent)
{
	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep{ ",.`~@#$%^&*-_+=(){}[]<>\/|?':;!\n " }; //characters to disregard/supress
	tokenizer tok{ FileContent, sep };
	for (auto t : tok) {
		boost::algorithm::to_lower(t);
		this->words.push_back(t);
		this->wordsSize = words.size();  //Calculate vector size
	}
}

void Map::emmitter(string key, string value, string tmpFileName, FileManagement &fileObj)
{
	const string keyValueParse = key + "," + value;
	fileObj.writeToTmpFile(tmpFileName, keyValueParse);
}