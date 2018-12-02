////////////////////////////////////////////////////////////////////////////////
// test.cpp - Google Unit Test for testing Map Reduce public member functions 														
// Language:    C++, Visual Studio 2017												
// Platform:    Microsoft Surface Pro 4, Windows 10									
// Application: Project 1, Single Node Map/Reduce Program							
// Author:      Bubah Conteh, Syracuse University CSE 687 - Object Oriented Design	
//              bconteh@syr.edu														
////////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include <Windows.h>
#include "../MRFrameWork/sort.h"
#include "../MRFrameWork/filemanagement.h"
#include "../MRFrameWork/filemanagement.cpp"
#include "../MRFrameWork/directory_management.h"
#include "../MRFrameWork/directory_management.cpp"
#include "C:/Users/conte/Documents/MapReduce/MapReduce/map.h"
#include "C:/Users/conte/Documents/MapReduce/MapReduce/Reduce.h"

typedef std::vector < std::pair < std::string, std::string>> vector_pair_str;

std::string input_dir = "C:\\testInput";
std::string temp_dir = "C:\\testTemp";
std::string output_dir = "C:\\testOutput";
std::string dll_dir = "C:\\Users\\conte\\Documents\\MyDLL\\MapReduce.dll";

void EmptyBuffer(vector_pair_str *buffered_memory, size_t buffer, std::string filename, std::string input_dir, std::string temp_dir, std::string output_dir, std::string dll_dir) {
	if (buffered_memory->size() >= buffer) { // if buffer reaches cap write data to disk and clear buffer
		FileManagement fmobj(input_dir, temp_dir, output_dir, dll_dir);
		fmobj.WriteToTempFile(filename, *buffered_memory, temp_dir);
		buffered_memory->clear();
	}
}

// Funtion exports Key/Value pair from Map to buffer
void Emit(std::string key, std::string value, std::string filename, size_t buffer, std::string inputDir,
	std::string tempDir, std::string outputDir, std::string dll_dir, vector_pair_str *buffered_memory) {
	std::pair<std::string, std::string> key_value; // Declare a temp variable to store key/value pair
	key_value.first = key;
	key_value.second = value;
	buffered_memory->push_back(key_value); // push key/value pair to buffer in memmory
	EmptyBuffer(buffered_memory, buffer, filename, inputDir, tempDir, outputDir, dll_dir);

}

struct Map_Test : public testing::Test {
	vector_pair_str *bufferedMemory;
	MapInterface* mp;
	void SetUp() {
		typedef MapInterface*(*myFNPTR)(size_t);
		fs::directory_iterator tmpDir_Itr{ "C:\\testTemp" }; // pointer to first file in interm directory
		fs::path tempFile_Path{ *tmpDir_Itr }; // path to first file in interm directory
		fs::ofstream ofs{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
		ofs.close(); // Close file
		HINSTANCE hInst = LoadLibrary(L"C:\\Users\\conte\\Documents\\MyDll\\MapReduce.dll");
		myFNPTR fn = (myFNPTR)GetProcAddress(hInst, "CreateMap");
		mp = fn(3);
		bufferedMemory = new vector_pair_str(); // Memory buffer passed to Map function
	}

	void TearDown() {
		delete bufferedMemory;
		delete mp;
	}
};

struct Reduce_Test : public testing::Test {
	ReduceInterface* reduce;
	void SetUp() {
		typedef ReduceInterface*(*myFNPTR)(std::string);
		fs::directory_iterator tmpDir_Itr{ "C:\\testTemp" }; // pointer to first file in interm directory
		fs::path tempFile_Path{ *tmpDir_Itr }; // path to first file in interm directory
		fs::ofstream ofs{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
		ofs.close(); // Close file
		HINSTANCE hInst = LoadLibrary(L"C:\\Users\\conte\\Documents\\MyDll\\MapReduce.dll");
		myFNPTR fn = (myFNPTR)GetProcAddress(hInst, "CreateReduce");
		reduce = fn(output_dir);
	}

	void TearDown() {
		delete reduce;
	}
};

TEST_F(Map_Test, test1) {

	FileManagement fm(input_dir, temp_dir, output_dir, dll_dir);
	DirectoryManagement dm(input_dir, temp_dir, output_dir, dll_dir);
	const std::string s1{ "C:\\testTemp\\test.txt" };

	//Act
	mp->Mapper(dm.GetInputFilename(), "", s1, input_dir, temp_dir, output_dir, dll_dir, Emit, bufferedMemory);
	std::string tmpFileContent = fm.ReadFromTempFile(s1, dm.GetTempDir());

	//Assert
	ASSERT_STREQ(tmpFileContent.c_str(), "");
}

TEST_F(Map_Test, test2) {

	FileManagement fm(input_dir, temp_dir, output_dir, dll_dir);
	DirectoryManagement dm(input_dir, temp_dir, output_dir, dll_dir);
	const std::string s1{ "C:\\testTemp\\test.txt" };

	//Act
	mp->Mapper(dm.GetInputFilename(), "MR*(Project^@two", s1, input_dir, temp_dir, output_dir, dll_dir, Emit, bufferedMemory);
	std::string tmpFileContent = fm.ReadFromTempFile("C:\\testTemp\\test.txt", dm.GetTempDir());

	//Assert
	ASSERT_STREQ(tmpFileContent.c_str(), "mr,1 project,1 two,1 ");
}

TEST_F(Map_Test, test3) {

	FileManagement fm(input_dir, temp_dir, output_dir, dll_dir);
	DirectoryManagement dm(input_dir, temp_dir, output_dir, dll_dir);
	const std::string s1{ "C:\\testTemp\\test.txt" };

	//Act
	mp->Mapper(dm.GetInputFilename(), "& () %^#$@*!+=_", s1, input_dir, temp_dir, output_dir, dll_dir, Emit, bufferedMemory);
	std::string tmpFileContent = fm.ReadFromTempFile("C:\\testTemp\\test.txt", dm.GetTempDir());

	//Assert
	ASSERT_STREQ(tmpFileContent.c_str(), "");
}

TEST(sort, test1) {
	//Arrange - Test sort class with string input
	Sort<std::string> st("C D G J K A");  // Sort constructor takes (1) string input param

	//Act
	st.SortData(); // Public member function sorts member data 
	std::vector<std::string> myVec = st.ExportSortedData(); // Return sorted vector

	//Assert
	ASSERT_EQ(myVec[0], "A");
	ASSERT_EQ(myVec[1], "C");
	ASSERT_EQ(myVec[2], "D");
	ASSERT_EQ(myVec[3], "G");
	ASSERT_EQ(myVec[4], "J");
	ASSERT_EQ(myVec[5], "K");

	//Arrange - Test sort class with vector input
	std::vector<std::string> myVec1(3);
	myVec1[0] = "C";
	myVec1[1] = "D";
	myVec1[2] = "A";
	
	//Act
	Sort<std::vector<std::string>> st2(myVec1);

	//Assert
	ASSERT_EQ(myVec1[0], "A");
	ASSERT_EQ(myVec1[1], "C");
	ASSERT_EQ(myVec1[2], "D");


	//Arrange - Test sort class with vector<str, str> input
	std::vector<std::pair<std::string, std::string>> myVec2(3);

	std::pair<std::string, std::string> A;
	std::pair<std::string, std::string> B;
	std::pair<std::string, std::string> C;

	A.first = "testing";
	A.second = "1";
	B.first = "fileManager";
	B.second = "2";
	C.first = "class";
	C.second = "3";

	myVec2[0] = A;
	myVec2[1] = B;
	myVec2[2] = C;

	//Act
	Sort<std::vector<std::pair<std::string, std::string>>> st3(myVec2);

	//Assert
	ASSERT_EQ(myVec2[0].first, "class");
	ASSERT_EQ(myVec2[1].first, "fileManager");
	ASSERT_EQ(myVec2[2].first, "testing");
}

TEST_F(Reduce_Test, Test1) {

	//Arrange
	FileManagement fm(input_dir, temp_dir, output_dir, dll_dir); // Instantiate file object

	std::string myStr{ "google,1 unit,1 test,1 for,1, reduce,1 class,1 public,1 methods,1 this,1 test,1 has,1 a,1, total,1 of,1 twentytwo,1 words,1 but,1 nineteen,1 are, 1 unique,1 words,1 test,1 " };
	std::vector<std::pair<std::string, std::string>> myVec(19);

	myVec = reduce->Reducer(myStr);

	//Assert
	ASSERT_EQ(myVec[0].first, "google"); ASSERT_EQ(myVec[0].second, "1");
	ASSERT_EQ(myVec[1].first, "unit"); ASSERT_EQ(myVec[1].second, "1");
	ASSERT_EQ(myVec[2].first, "test"); ASSERT_EQ(myVec[2].second, "3");
	ASSERT_EQ(myVec[3].first, "for"); ASSERT_EQ(myVec[3].second, "1");
	ASSERT_EQ(myVec[4].first, "reduce"); ASSERT_EQ(myVec[4].second, "1");
	ASSERT_EQ(myVec[5].first, "class"); ASSERT_EQ(myVec[5].second, "1");
	ASSERT_EQ(myVec[6].first, "public"); ASSERT_EQ(myVec[6].second, "1");
	ASSERT_EQ(myVec[7].first, "methods"); ASSERT_EQ(myVec[7].second, "1");
	ASSERT_EQ(myVec[8].first, "this"); ASSERT_EQ(myVec[8].second, "1");
	ASSERT_EQ(myVec[9].first, "has"); ASSERT_EQ(myVec[9].second, "1");
	ASSERT_EQ(myVec[10].first, "a"); ASSERT_EQ(myVec[10].second, "1");
	ASSERT_EQ(myVec[11].first, "total"); ASSERT_EQ(myVec[11].second, "1");
	ASSERT_EQ(myVec[12].first, "of"); ASSERT_EQ(myVec[12].second, "1");
	ASSERT_EQ(myVec[13].first, "twentytwo"); ASSERT_EQ(myVec[13].second, "1");
	ASSERT_EQ(myVec[14].first, "words"); ASSERT_EQ(myVec[14].second, "2");
	ASSERT_EQ(myVec[15].first, "but"); ASSERT_EQ(myVec[15].second, "1");
	ASSERT_EQ(myVec[16].first, "nineteen"); ASSERT_EQ(myVec[16].second, "1");
	ASSERT_EQ(myVec[17].first, "are"); ASSERT_EQ(myVec[17].second, "1");
	ASSERT_EQ(myVec[18].first, "unique"); ASSERT_EQ(myVec[18].second, "1");

}

TEST(DirectoryManager_TEST, Test1) {
	DirectoryManagement dm(input_dir, temp_dir, output_dir, dll_dir);

	ASSERT_EQ(dm.GetInputDir(), "C:\\testInput");
	ASSERT_EQ(dm.GetTempDir(), "C:\\testTemp");
	ASSERT_EQ(dm.GetOutputDir(), "C:\\testOutput");

}

TEST(FileManager_Test, Test1) {
	//Arrange
	FileManagement fm(input_dir, temp_dir, output_dir, dll_dir);
	DirectoryManagement dm(input_dir, temp_dir, output_dir, dll_dir);
	fs::directory_iterator tempDir_Itr{ "C:\\testTemp" };
	fs::path tempFile_Path{ *tempDir_Itr }; // path to first file in temp directory

	fs::ofstream ofs2{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
	ofs2.close(); // Close file
	std::vector<std::string> vec_str(1);

	vec_str[0] = "testing temp file";

	//Act
	fm.WriteToTempFile("C:\\testTemp\\test.txt", vec_str, dm.GetTempDir()); // Writes to temp file

	//Assert
	ASSERT_EQ(fm.ReadFromTempFile(dm.GetTempFilename(), dm.GetTempDir()), "testing temp file ");
}

TEST(FileManager_Test, Test2) {

	//Arrange
	FileManagement fm(input_dir, temp_dir, output_dir, dll_dir);
	DirectoryManagement dm(input_dir, temp_dir, output_dir, dll_dir);
	fs::directory_iterator tempDir_Itr{ "C:\\testTemp" };
	fs::path tempFile_Path{ *tempDir_Itr }; // path to first file in temp directory

	fs::ofstream ofs2{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content

	ofs2.close(); // Close file

	std::vector<std::pair<std::string, std::string>> myVec2(3);

	std::pair<std::string, std::string> A;
	std::pair<std::string, std::string> B;
	std::pair<std::string, std::string> C;

	A.first = "testing";
	A.second = "1";
	B.first = "FileManager";
	B.second = "2";
	C.first = "class";
	C.second = "3";

	myVec2[0] = A;
	myVec2[1] = B;
	myVec2[2] = C;


	//ACT
	fm.WriteToTempFile("test.txt", myVec2, dm.GetTempDir()); // Writes to temp file

	//Assert
	ASSERT_EQ(fm.ReadFromTempFile("test.txt", dm.GetTempDir()), "testing FileManager Class ");
}