#include "Sort.h"
#include"KeyValue.h"

Sort::Sort(string fileContent) :sorted{false}
{
	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep{" "}; //characters to disregard/supress
	tokenizer tok{ fileContent, sep };

	for (const auto &t : tok) {
		this->wordsVector.push_back(t);
	}

	this->vectorSize = this->wordsVector.size();
}

void Sort::SortData() {

	for (int i = 0; i < vectorSize - 1; ++i) //Sorts class member data "wordsVector
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
	}

	sorted = true; // Sets class member data "sorted" to true

}

vector<string> Sort::exportSortedData()
{
	if (!sorted) {
		cout << "Data has not been sorted. Process will abort" << endl;
		abort();
	}

	return wordsVector;
}
