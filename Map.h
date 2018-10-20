#ifndef MAP_H
#define MAP_H

#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iostream>
#include <fstream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
namespace fs = boost::filesystem;

class Map
{
public:
	Map();
	void mapper(string, string, string);
	//export();
private:
	void tokenizer(string, string);
	void emmitter(string, string, string);
	size_t wordsSize; // number of records/words in 'words' vector
	vector<string> words;
	

};

#endif // !MAP_H

