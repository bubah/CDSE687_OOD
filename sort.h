////////////////////////////////////////////////////////////////////////////////
// Sort.h - Sorts intermediate key/value pair stored in temp directory				
// ver 2.0																			
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

namespace fs = boost::filesystem;

template <typename T>
class Sort{
public:

	// Constructor accepts sting param
	Sort(const std::string& fileContent);

	// Constructor accepts vector<string> param
	Sort(T&);

	void SortData();

	// Retuns vector of sorted data
	std::vector<T> ExportSortedData(); //returns sorted vector

private:

	// Stores data in vector 
	std::vector<std::string> wordsVector_;

	// Stores the size of this class's vector 
	size_t vectorSize_;

	// Tracks if vector sort funtion was invoked
	bool sorted_;
};

// Class constructor accepts string of raw data
template <typename T>
Sort<T>::Sort(const std::string& fileContent) :sorted_{ false }{
	BOOST_LOG_TRIVIAL(info) << "Instantiating a Sort object" << "\n";
	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep{ "\t\n " }; //characters to disregard/supress
	tokenizer tok{ fileContent, sep };

	for (const std::string &t : tok) { // Iterates through tokenizer
		this->wordsVector_.push_back(t); // push
	}

	this->vectorSize_ = this->wordsVector_.size();
}

template <typename T>
Sort<T>::Sort(T &fileContent) {
	BOOST_LOG_TRIVIAL(info) << "Instantiating a Sort object" << "\n";
	// Sort by key
	std::sort(fileContent.begin(), fileContent.end());
	sorted_ = true; // Sets class member data "sorted" to true
}

template <typename T>
void Sort<T>::SortData() {
	BOOST_LOG_TRIVIAL(info) << "Now running sortData function" << "\n";
	std::sort(wordsVector_.begin(), wordsVector_.end());
	sorted_ = true; // Sets class member data "sorted" to true
}

// Return the sorted data, otherwise notify user "not sorted"
template <typename T>
std::vector<T> Sort<T>::ExportSortedData() {
	BOOST_LOG_TRIVIAL(info) << "Now exporting Sorted data by invoking Sort class public method exportSortedData()" << "\n";
	
	if (!sorted_) { // If not sorted print to commandline
		BOOST_LOG_TRIVIAL(error) << "Data has not been sorted. Process is terminating.." << "\n";
	}

	return wordsVector_;
}

#endif // SORT_H
