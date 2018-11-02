////////////////////////////////////////////////////////////////////////////////
// Sort.h - Sorts intermediate key/value pair stored in temp directory				
// ver 1.0																			
// Language:    C++, Visual Studio 2017												
// Platform:    Microsoft Surface Pro 4, Windows 10									
// Application: Project 1, Single Node Map/Reduce Program							
// Author:      Bubah Conteh, Syracuse University CSE 687 - Object Oriented Design	
//              bconteh@syr.edu														
////////////////////////////////////////////////////////////////////////////////

#ifndef SORT_H
#define SORT_H

#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/log/trivial.hpp>
#include <boost/tokenizer.hpp>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
using std::string;
namespace fs = boost::filesystem;

class Sort
{
public:
	Sort() {};

	 // Constructor accepts sting param
	Sort(string); 

	// Constructor accepts vector<string> param
	Sort(vector<string>);

	// Sorts data recived from the map class
	void sortVectorData( vector<std::pair<std::string, int>> & );

	// Sorts data within member data 'wordsVector'
	void SortData();

	// Retuns vector of sorted data
	vector<string> exportSortedData(); //returns sorted vector

private:

	// Stores data in vector 
	vector<string> wordsVector;

	// Stores the size of this class's vector 
	size_t vectorSize;

	// Tracks if vector sort funtion was invoked
	bool sorted;
};

#endif // !SORT_H