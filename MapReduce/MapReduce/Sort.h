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

template <typename T>
class Sort
{
public:
	Sort() {};

	 // Constructor accepts sting param

	Sort(string); 

	// Constructor accepts vector<string> param
	Sort(T&);

	// Sorts data recived from the map class
	//void sortVectorData( vector<std::pair<std::string, int>> & );
	//void sortVectorData(T &);
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

template <typename T>
Sort<T>::Sort(T &fileContent)
{
	BOOST_LOG_TRIVIAL(info) << "Now invoking Sort Class public method sortVectorData(vector<string, int> &) to sort data" << "\n";
	// Sort by key
	std::sort(fileContent.begin(), fileContent.end());
	sorted = true; // Sets class member data "sorted" to true
}

// Class constructor accepts string of raw data
template <typename T>
Sort<T>::Sort(string fileContent) :sorted{ false }
{
	BOOST_LOG_TRIVIAL(info) << "Instantiating a Sort object using constructor Sort(string)" << "\n";
	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep{ "\t\n " }; //characters to disregard/supress
	tokenizer tok{ fileContent, sep };

	for (const auto &t : tok) {
		this->wordsVector.push_back(t);
	}

	this->vectorSize = this->wordsVector.size();
}


// Class constructor Overloaded to accept vector of string data
/*template <typename T>
Sort<T>::Sort(T& fileContent) :sorted{ false }
{
	BOOST_LOG_TRIVIAL(info) << "Instantiating a Sort object using constructor Sort(vector<string>)" << "\n";
	for (const auto &t : fileContent) {
		this->wordsVector.push_back(t);
	}
	this->vectorSize = this->wordsVector.size();
}*/


// Overloaded to accept a vector of pairs as file content input and std::sort
/*template<typename T>
//void Sort::sortVectorData( vector<std::pair<std::string, int>> &fileContent )
void Sort::sortVectorData( T &fileContent )
{
	BOOST_LOG_TRIVIAL(info) << "Now invoking Sort Class public method sortVectorData(vector<string, int> &) to sort data" << "\n";
	// Sort by key
	std::sort(fileContent.begin(), fileContent.end());
	sorted = true; // Sets class member data "sorted" to true
}*/

template <typename T>
void Sort<T>::SortData() {
	BOOST_LOG_TRIVIAL(info) << "Now invoking Sort Class public method sortData() to sort private data member vector<string>" << "\n";
	std::sort(wordsVector.begin(), wordsVector.end());
	sorted = true; // Sets class member data "sorted" to true

}


// Return the sorted data, otherwise notify user "not sorted"
template <typename T>
vector<string> Sort<T>::exportSortedData()
{
	BOOST_LOG_TRIVIAL(info) << "Now exporting Sorted data by invoking Sort class public method exportSortedData()" << "\n";
	if (!sorted) {
		BOOST_LOG_TRIVIAL(error) << "Data has not been sorted. Process is terminating.." << "\n";
		abort();
	}

	return wordsVector;
}
#endif // !SORT_H