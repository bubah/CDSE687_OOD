#include "Map.h"
#include "FileManagement.h"


Map::Map() :wordsSize{ 0 } {}

void Map::mapper(string inputFileName, string FileContent, string tmpFileName) {
	tokenizer(FileContent);
	for (string word : words) {
		emmitter(word, "1", tmpFileName);
	}
}

void Map::tokenizer(string FileName, string FileContent)
{
	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep{ ",.`~@#$%^&*-_+=(){}[]<>\/|?':; " }; //characters to disregard/supress
	tokenizer tok{ FileContent, sep };
	for (const auto &t : tok) {
		this->words.push_back(t);
		this->wordsSize = words.size();  //Calculate vector size
		std::cout << t << '\n';
	}
}

void Map::emmitter(string key, string value, string tmpFileName)
{
	
}
