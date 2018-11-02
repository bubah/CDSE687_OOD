////////////////////////////////////////////////////////////////////////////////
// test.cpp - Google Unit Test for testing Map Reduce public member functions 														
// Language:    C++, Visual Studio 2017												
// Platform:    Microsoft Surface Pro 4, Windows 10									
// Application: Project 1, Single Node Map/Reduce Program							
// Author:      Bubah Conteh, Syracuse University CSE 687 - Object Oriented Design	
//              bconteh@syr.edu														
////////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "../MapReduce/Map.cpp"
#include "../MapReduce/FileManagement.cpp"
#include "../MapReduce/Sort.cpp"


TEST(MapTest, Test_Mapper_n_Export_On_Empty_Data) {
	fs::directory_iterator tmpDir_Itr{ "C:\\testTemp" }; // pointer to first file in interm directory
	fs::path tempFile_Path{ *tmpDir_Itr }; // path to first file in interm directory
	fs::ofstream ofs{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
	ofs.close(); // Close file

	FileManagement fm("C:\\testInput", "C:\\testTemp", "C:\\testOutput");
	const string s1{ "C:\\testTemp\\test.txt" };
	Map mp;
	mp.mapper(fm.getInputFileName(), "", fm.getTmpFileName(), fm);
	mp.exportt(s1, fm);

	//Act
	string tmpFileContent = fm.readFromTmpFile(fm.getTmpFileName());

	//Assert
	ASSERT_STREQ(tmpFileContent.c_str(), "");
}

TEST(MapTest, Test_Mapper_n_Export_on_One_WordToken) {
	//Arrange
	fs::directory_iterator tmpDir_Itr{ "C:\\testTemp" }; // pointer to first file in interm directory
	fs::path tempFile_Path{ *tmpDir_Itr }; // path to first file in interm directory
	fs::ofstream ofs{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
	ofs.close(); // Close file

	FileManagement fm("C:\\testInput", "C:\\testTemp", "C:\\testOutput");
	const string s1{ "C:\\testTemp\\test.txt" };
	Map mp;
	mp.mapper(fm.getInputFileName(), "*oneword&#", fm.getTmpFileName(), fm);
	mp.exportt(s1, fm);

	//Act
	string tmpFileContent = fm.readFromTmpFile(fm.getTmpFileName());

	//Assert
	ASSERT_STREQ(tmpFileContent.c_str(), "oneword,1 ");
}


TEST(MapTest, Test_Mapper_n_Export_on_Two_Word_Token) {
	//Arrange
	fs::directory_iterator tmpDir_Itr{ "C:\\testTemp" }; // pointer to first file in interm directory
	fs::path tempFile_Path{ *tmpDir_Itr }; // path to first file in interm directory
	fs::ofstream ofs{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
	ofs.close(); // Close file

	FileManagement fm("C:\\testInput", "C:\\testTemp", "C:\\testOutput");
	const string s1{ "C:\\testTemp\\test.txt" };
	Map mp;
	mp.mapper(fm.getInputFileName(), "*two&#! words() ", fm.getTmpFileName(), fm);
	mp.exportt(s1, fm);

	//Act
	string tmpFileContent = fm.readFromTmpFile(fm.getTmpFileName());

	//Assert
	ASSERT_STREQ(tmpFileContent.c_str(), "two,1 words,1 ");
}

TEST(MapTest, Test_Mapper_n_Export_func_string_of_punctuations) {
	//Arrange
	fs::directory_iterator tmpDir_Itr{ "C:\\testTemp" }; // pointer to first file in interm directory
	fs::path tempFile_Path{ *tmpDir_Itr }; // path to first file in interm directory
	fs::ofstream ofs{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
	ofs.close(); // Close file

	FileManagement fm("C:\\testInput", "C:\\testTemp", "C:\\testOutput");
	const string s1{ "C:\\testTemp\\test.txt" };
	Map mp;
	mp.mapper(fm.getInputFileName(), "	~`!@#$%^&*()-_=+{}[]:;'<>,.?/|\ ", fm.getTmpFileName(), fm);
	mp.exportt(s1, fm);

	//Act
	string tmpFileContent = fm.readFromTmpFile(fm.getTmpFileName());

	//Assert
	ASSERT_STREQ(tmpFileContent.c_str(), "");
}


TEST(FileMgrTest, Test_Constr_n_getterfunctions) {
	FileManagement fm("C:\\testInput", "C:\\testTemp", "C:\\testOutput");

	fs::path inPath = fm.getInputDir();

	fs::path tmpPath = fm.getTempDir();

	//Assert
	ASSERT_EQ(inPath, "C:\\testInput");
	ASSERT_EQ(tmpPath, "C:\\testTemp");

}

TEST(FileMgrTest, Test_write_read_functions_w_string_input) {
	//Arrange
	FileManagement fm("C:\\testInput", "C:\\testTemp", "C:\\testOutput"); // The proceeding directories must exist in your C drive for this test.
	fs::directory_iterator inputDir_Itr{ "C:\\testInput" }; // points to first file in input directory
	fs::path inputFile_Path{ *inputDir_Itr }; // path to first file in input directory
	fs::directory_iterator tempDir_Itr{ "C:\\testTemp" };
	fs::path tempFile_Path{ *tempDir_Itr }; // path to first file in temp directory
	fs::directory_iterator outputDir_Itr{ "C:\\testOutput" };
	fs::path outputFile_Path{ *outputDir_Itr }; // path to first file in output directory



	fs::ofstream ofs{ inputFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
	fs::ofstream ofs2{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
	fs::ofstream ofs3{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
	ofs.close(); // Close file
	ofs2.close(); // Close file
	ofs3.close(); // Close file

	//Act
	fm.writeToInputFile(fm.getInputFileName(), "testing input file"); // Writes to input file
	fm.writeToTmpFile(fm.getTmpFileName(), "testing temp file"); // Writes to temp file
	fm.writeToOutputFile(fm.getOutputFileName(), "testing output file"); // Writes to output file

	//Assert
	ASSERT_EQ(fm.readFromInputFile(fm.getInputFileName()), "testing input file ");
	ASSERT_EQ(fm.readFromInputFile(fm.getInputFileName()), "testing temp file ");
	ASSERT_EQ(fm.readFromInputFile(fm.getInputFileName()), "testing output file ");
}

TEST(FileMgrTest, Test_write_read_functions_w_vector_input) {

	//Arrange
	FileManagement fm("C:\\testInput", "C:\\testTemp", "C:\\testOutput"); // The proceeding directories must exist in your C drive for this test.
	fs::directory_iterator inputDir_Itr{ "C:\\testInput" }; // points to first file in input directory
	fs::path inputFile_Path{ *inputDir_Itr }; // path to first file in input directory
	fs::directory_iterator tempDir_Itr{ "C:\\testTemp" };
	fs::path tempFile_Path{ *tempDir_Itr }; // path to first file in temp directory
	fs::directory_iterator outputDir_Itr{ "C:\\testOutput" };
	fs::path outputFile_Path{ *outputDir_Itr }; // path to first file in output directory


	fs::ofstream ofs2{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
	fs::ofstream ofs3{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
	ofs2.close(); // Close file
	ofs3.close(); // Close file

	vector<string> myVec(3);
	vector<std::pair<string, int>> myVec2(3);

	std::pair<string, int> A;
	std::pair<string, int> B;
	std::pair<string, int> C;

	A.first = "testing";
	A.second = 1;
	B.first = "FileManager";
	B.second = 2;
	C.first = "class";
	C.second = 3;

	myVec[0] = "testing";
	myVec[1] = "write";
	myVec[2] = "function";

	myVec2[0] = A;
	myVec2[1] = B;
	myVec2[2] = C;


	//ACT
	fm.writeToTmpFile(fm.getTmpFileName(), myVec); // Writes to temp file
	fm.writeToOutputFile(fm.getOutputFileName(), myVec2); // Writes to output file

	//ASSERT
	ASSERT_EQ(fm.readFromTmpFile(fm.getTmpFileName()), "testing write function ");
	ASSERT_EQ(fm.readFromOutputFile(fm.getOutputFileName()), "testing FileManager class ");
}

TEST(SortTest, Test_Sort_public_methds)
{
	//Arrange - Test sort class with string input
	Sort st("C D G J K A");  // Sort constructor takes (1) string input param
	
	//Act
	st.SortData(); // Public member function sorts member data 
	vector<string> myVec = st.exportSortedData(); // Return sorted vector

	//Assert
	ASSERT_EQ(myVec[0], "A");
	ASSERT_EQ(myVec[1], "C");
	ASSERT_EQ(myVec[2], "D");
	ASSERT_EQ(myVec[3], "G");
	ASSERT_EQ(myVec[4], "J");
	ASSERT_EQ(myVec[5], "K");

	//Arrange - Test sort class with vector input
	vector<string> myVec1(3);
	myVec1[0] = "C";
	myVec1[1] = "D";
	myVec1[2] = "A";
	Sort st2(myVec1);

	//Act
	st2.SortData();
	vector<string> myVec2 = st2.exportSortedData();

	//Assert
	ASSERT_EQ(myVec2[0], "A");
	ASSERT_EQ(myVec2[1], "C");
	ASSERT_EQ(myVec2[2], "D");

}

TEST(SortTest, Test_Sort_methds_w_ref_to_vector)
{
	//Arrange
	Sort st;  // Sort constructor takes string input stores in member data (vector)
	vector<std::pair<string, int>> myVec(3);

	std::pair<string, int> A;
	std::pair<string, int> B;
	std::pair<string, int> C;

	A.first = "testing";
	A.second = 1;
	B.first = "fileManager";
	B.second = 2;
	C.first = "class";
	C.second = 3;

	myVec[0] = A;
	myVec[1] = B;
	myVec[2] = C;

	//Act
	st.sortVectorData(myVec);

	//Assert
	ASSERT_EQ(myVec[0].first, "class");
	ASSERT_EQ(myVec[1].first, "fileManager");
	ASSERT_EQ(myVec[2].first, "testing");

}


