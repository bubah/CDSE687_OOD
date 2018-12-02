#include "reduce.h"

#ifdef MAPREDUCE_EXPORTS
#define MAPREDUCE_API __declspec(dllexport)
#endif

namespace ios = boost::iostreams;
namespace bm = boost::bimaps;

struct counter {
	counter() : c(0) {}
	counter& operator++() { ++c; return *this; }
	unsigned int operator++(int) { return c++; }
	operator const unsigned int() const { return c; }

private:
	unsigned int c;
};

class MAPREDUCE_API Reduce : public ReduceInterface {
public:
	Reduce();
	Reduce(std::string);
	~Reduce();
	std::vector< std::pair<string, string> > Reducer(std::string);

	// Aggregates the data and sums up repeated keys
	void SumResults(std::string);

	// Getter for the output vector data
	std::vector< std::pair<std::string, std::string> > GetOutputVector();
private:

	// Saves data to the output vector private data member
	void _exportResults(std::string, std::string);

	std::vector< std::pair<std::string, std::string> > _outputVector;

	// Contains the output directory location
	std::string _dirOutput;

	// Contains the temporary directory location
	std::string _dirTemp;
};

extern "C" MAPREDUCE_API ReduceInterface* CreateReduce(std::string str) {
	return new Reduce(str);
}

Reduce::Reduce() { BOOST_LOG_TRIVIAL(info) << "Instantiating a Reduce object" << "\n"; }

Reduce::Reduce(std::string outPutDir) :_dirOutput(outPutDir) { BOOST_LOG_TRIVIAL(info) << "Instantiating a Reduce object" << "\n"; }

Reduce::~Reduce() {}

std::vector < std::pair<string, string> > Reduce::Reducer(string tmpData) {
	BOOST_LOG_TRIVIAL(info) << "Now running Reducer function" << "\n";

	SumResults(tmpData);

	// Return the data as a vector of pairs
	return GetOutputVector();
}

// Sum up the repeated tokens (regardless of case) and send to output vector
void Reduce::SumResults(string mapData) {
	BOOST_LOG_TRIVIAL(info) << "Now running sumResults function" << "\n";
	typedef bm::bimap <bm::unordered_set_of <std::string>, bm::list_of <counter> > word_counter;
	typedef boost::tokenizer<boost::char_separator<char> > text_tokenizer;

	// Feed the text into the container
	word_counter wc;
	text_tokenizer tok(mapData, boost::char_separator<char>("1 \t\n.,;:!?'\"-"));

	// Sum up the tokens
	for (text_tokenizer::const_iterator it = tok.begin(), it_end = tok.end(); it != it_end; ++it) {
		++wc.left[*it];
	}

	// Send the output to the vector private data member 
	for (word_counter::right_const_iterator wit = wc.right.begin(), wit_end = wc.right.end(); wit != wit_end; ++wit) {
		_exportResults(wit->second, std::to_string(wit->first));
	}
}

// Getter for the output vector
std::vector < std::pair<std::string, std::string> > Reduce::GetOutputVector() {
	BOOST_LOG_TRIVIAL(info) << "Now runnnig getOutputVector function" << "\n";
	return _outputVector;
}

// Write out the results to the output folder
void Reduce::_exportResults(std::string key, std::string value) {
	// Sort by key
	_outputVector.push_back(std::make_pair(key, value));
}
