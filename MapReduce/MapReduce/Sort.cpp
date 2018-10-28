//////////////////////////////////////////////////////////////////////////////////////
// Sort.cpp - Sorts intermediate key/value pair stored in temp directory			//
// ver 1.0																			//
// Language:    C++, Visual Studio 2017												//
// Platform:    Microsoft Surface Pro 4, Windows 10									//
// Application: Project 1, Single Node Map/Reduce Program							//
// Author:      Bubah Conteh, Syracuse University CSE 687 - Object Oriented Design	//
//              bconteh@syr.edu														//
//////////////////////////////////////////////////////////////////////////////////////

#include "Sort.h"

Sort::Sort(string fileContent) :sorted{ false }
{
	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep{ "	 " }; //characters to disregard/supress
	tokenizer tok{ fileContent, sep };

	for (const auto &t : tok) {
		this->wordsVector.push_back(t);
	}

	this->vectorSize = this->wordsVector.size();
}

// Overloaded to accept a vector of pairs as file content input and std::sort
void Sort::sortVectorData( vector<std::pair<std::string, int>> &fileContent )
{
	// Sort by key
	std::sort(fileContent.begin(), fileContent.end());
}

void Sort::SortData() {

	/*for (int i = 0; i < vectorSize - 1; ++i) //Sorts class member data "wordsVector
	{
		for (int j = i + 1; j < vectorSize; ++j)
		{
			if (wordsVector[i] > wordsVector[j])
			{
				string temp = wordsVector[i];
				wordsVector[i] = wordsVector[j];
				wordsVector[j] = temp;
			}
		}
	}*/
	std::sort(wordsVector.begin(), wordsVector.end());
	sorted = true; // Sets class member data "sorted" to true

}

// Return the sorted data, otherwise notify user "not sorted"
vector<string> Sort::exportSortedData()
{
	if (!sorted) {
		cout << "Data has not been sorted. Process will abort" << endl;
		abort();
	}

	return wordsVector;
}