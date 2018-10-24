#ifndef SORT_H
#define SORT_H

//////////////////////////////////////////////////////////////////////////////////////
// Sort.h - Sorts intermediate key/value pair stored in temp directory				//
// ver 1.0																			//
// Language:    C++, Visual Studio 2017												//
// Platform:    Microsoft Surface Pro 4, Windows 10									//
// Application: Project 1, Single Node Map/Reduce Program							//
// Author:      Bubah Conteh, Syracuse University CSE 687 - Object Oriented Design	//
//              bconteh@syr.edu														//
//////////////////////////////////////////////////////////////////////////////////////

#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/tokenizer.hpp>
#include <iostream>
#include<vector>
#include "KeyValue.h"
using std::cout;
using std::endl;
using std::vector;
using std::string;
namespace fs = boost::filesystem;

class Sort
{
public:
	Sort(string);
	void SortData();
	vector<string> exportSortedData();
private:
	vector<string> wordsVector;
	int vectorSize;
	bool sorted;
};

#endif