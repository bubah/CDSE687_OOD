////////////////////////////////////////////////////////////////////////////////
// WordCountMap.cpp -	Defines Map Implementation, derived from 
//					MapInterface version 1.0
// Language:    C++, Visual Studio 2017										
// Platform:    Microsoft Surface Pro 4, Windows 10								
// Application: Project 1, Single Node Map/Reduce Program							
// Author:      Bubah Conteh 
//				Syracuse University CSE 687 - Object Oriented Design
//              bconteh@syr.edu														
////////////////////////////////////////////////////////////////////////////////

#include "map.h"

#ifdef MAPREDUCE_EXPORTS
#define MAPREDUCE_API __declspec(dllexport)
#endif

// WordCount version of Map Class
class  MAPREDUCE_API WordCountMap : public MapInterface {
public:

	//Default Constr
	WordCountMap(size_t buffer=0);

	// Mapper Function
	void Mapper(const std::string inputFileName, const std::string FileContent,
		const std::string tmpFileName, std::string inputDir, std::string tempDir, std::string, std::string,
		void(*FNPTR_EMIT)(std::string, std::string, std::string, size_t buffer,
			std::string, std::string, std::string, std::string, std::vector<std::pair<std::string, std::string>> *bufferMemory),
		std::vector<std::pair<std::string, std::string>> *bufferMemory);

private:

	// Tokenize input data
	std::vector<std::string> Tokenizer(const std::string fileContent);
};

extern "C" MAPREDUCE_API MapInterface* CreateMap(size_t buffer) {
		return new WordCountMap(buffer);
	}

WordCountMap::WordCountMap(size_t bufferSize) { SetBufferCap(bufferSize); }

void WordCountMap::Mapper(const std::string inputFileName, const std::string FileContent, 
	const std::string tmpFileName, std::string inputDir, std::string tempDir, std::string outputDir, std::string dll_dir,
	void(*FNPTR_EMIT)(std::string, std::string, std::string, size_t buffer,
	std::string, std::string, std::string, std::string, std::vector<std::pair<std::string, std::string>> *bufferMemory),
	std::vector<std::pair<std::string, std::string>> *bufferMemory) {

	BOOST_LOG_TRIVIAL(info) << "Now running Mapper function" << "\n";

	std::vector<std::string> tokenizedData = Tokenizer(FileContent); // Tokenize input data
	std::string value = "1"; // value for each unique word occurrence

	// Invoke export function on each word/value pair
	for (std::string word : tokenizedData) {
		FNPTR_EMIT(word, value, tmpFileName, GetBufferCap(), inputDir, tempDir, outputDir, dll_dir, bufferMemory); // function pointer
	}

}

std::vector<std::string> WordCountMap::Tokenizer(const std::string FileContent) {

	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep{ "	,.`~@#$%^&*-_+=(){}[]<>\/|?':;!\t\n " }; // characters to disregard/supress
	tokenizer tok{ FileContent, sep };
	std::vector<std::string> tokenizedData;
	for (std::string t : tok) {
		boost::algorithm::to_lower(t); // set words to lower case
		tokenizedData.push_back(t);  // push word to back of vector
	}

	return tokenizedData;
}
