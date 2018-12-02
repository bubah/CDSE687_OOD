////////////////////////////////////////////////////////////////////////////////
// test.cpp - Google Unit Test for testing Map Reduce public member functions 														
// Language:    C++, Visual Studio 2017												
// Platform:    Microsoft Surface Pro 4, Windows 10									
// Application: Project 1, Single Node Map/Reduce Program							
// Author:      Bubah Conteh, Syracuse University CSE 687 - Object Oriented Design	
//              bconteh@syr.edu														
////////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "C:\\Users\conte\Documents\MRFrameWork\MRFrameWork\FileManagement.h"
#include "C:\\Users\conte\Documents\MRFrameWork\MRFrameWork\Sort.h"


// Test Map Class public methods 'mapper' and 'exportt' on a empty string
TEST(MapTest, Test_Mapper_n_Export_On_Empty_Data) {

	//Arrange
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


// Test Map Class public methods 'mapper' and 'exportt' on a one token string
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


// Test Map Class public methods 'mapper' and 'exportt' on a two token string
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


// Test Map Class public methods 'mapper' and 'exportt' on a string punctuations
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


// Test FileManager constructor and directory getter-fucntions
TEST(FileMgrTest, Test_Constr_n_getterfunctions) {

	//Act
	FileManagement fm("C:\\testInput", "C:\\testTemp", "C:\\testOutput");

	fs::path inPath = fm.getInputDir();
	fs::path tmpPath = fm.getTempDir();
	fs::path outPath = fm.getOutputDir();

	//Assert
	ASSERT_EQ(inPath, "C:\\testInput");
	ASSERT_EQ(tmpPath, "C:\\testTemp");
	ASSERT_EQ(outPath, "C:\\testOutput");

}


// Test FileManager constructor and write to file methods (string input)
TEST(FileMgrTest, Test_write_read_functions_w_string_input) {

	//Arrange
	FileManagement fm("C:\\testInput\\", "C:\\testTemp\\", "C:\\testOutput\\"); // The proceeding directories must exist in your C drive for this test.
	fs::directory_iterator tempDir_Itr{ "C:\\testTemp" };
	fs::path tempFile_Path{ *tempDir_Itr }; // path to first file in temp directory
	fs::directory_iterator outputDir_Itr{ "C:\\testOutput" };
	fs::path outputFile_Path{ *outputDir_Itr }; // path to first file in output directory

	fs::ofstream ofs2{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
	fs::ofstream ofs3{ outputFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
	ofs2.close(); // Close file
	ofs3.close(); // Close file

	//Act
	fm.writeToTmpFile(fm.getTmpFileName(), "testing temp file"); // Writes to temp file
	fm.writeToOutputFile(fm.getOutputFileName(), "testing output file"); // Writes to output file

	//Assert
	ASSERT_EQ(fm.readFromTmpFile(fm.getTmpFileName()), "testing temp file ");
	ASSERT_EQ(fm.readFromOutputFile(fm.getOutputFileName()), "testing output file ");
}


// Test FileManager overloaded write methods (vector input)
TEST(FileMgrTest, Test_write_read_functions_w_vector_input) {

	//Arrange
	FileManagement fm("C:\\testInput", "C:\\testTemp", "C:\\testOutput"); // The proceeding directories must exist in your C drive for this test.
	fs::directory_iterator tempDir_Itr{ "C:\\testTemp" };
	fs::path tempFile_Path{ *tempDir_Itr }; // path to first file in temp directory
	fs::directory_iterator outputDir_Itr{ "C:\\testOutput" };
	fs::path outputFile_Path{ *outputDir_Itr }; // path to first file in output directory


	fs::ofstream ofs2{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
	fs::ofstream ofs3{ outputFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
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
	ASSERT_EQ(fm.readFromOutputFile(fm.getOutputFileName()), "testing: 1 FileManager: 2 class: 3 ");
}


// Test Sort Class public methods sortData() and exportSortedData()
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


// Test Sort Class public method sortVectorData()
TEST(SortTest, Test_Sort_methds_w_ref_to_vector)
{
	//Arrange
	Sort st;  // Instantiate Sort object using default constructor 
	vector<std::pair<string, int>> myVec(3);  // create a vector of key/value pairs

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
	st.sortVectorData(myVec); // Call Sort class public sort method to sort vector by reference

	//Assert
	ASSERT_EQ(myVec[0].first, "class");
	ASSERT_EQ(myVec[1].first, "fileManager");
	ASSERT_EQ(myVec[2].first, "testing");

}


// Test Reduce Class public method Reducer()
TEST(ReduceTest, Test_Reducer)
{
	//Arrange
	FileManagement fm("C:\\testInput", "C:\\testTemp", "C:\\testOutput"); // Instantiate file object
	Reduce rd(fm.getOutputDir().string());

	string myStr{ "google,1 unit,1 test,1 for,1, reduce,1 class,1 public,1 methods,1 this,1 test,1 has,1 a,1, total,1 of,1 twentytwo,1 words,1 but,1 nineteen,1 are, 1 unique,1 words,1 test,1 " };
	std::vector<std::pair<string, int>> myVec(19);

	//Act - Reducer should take in temp data as a string input and total the number of occurrences for each key
	myVec = rd.Reducer(myStr, fm); 

	//Assert
	ASSERT_EQ(myVec[0].first, "google"); ASSERT_EQ(myVec[0].second, 1);
	ASSERT_EQ(myVec[1].first, "unit"); ASSERT_EQ(myVec[1].second, 1);
	ASSERT_EQ(myVec[2].first, "test"); ASSERT_EQ(myVec[2].second, 3);
	ASSERT_EQ(myVec[3].first, "for"); ASSERT_EQ(myVec[3].second, 1);
	ASSERT_EQ(myVec[4].first, "reduce"); ASSERT_EQ(myVec[4].second, 1);
	ASSERT_EQ(myVec[5].first, "class"); ASSERT_EQ(myVec[5].second, 1);
	ASSERT_EQ(myVec[6].first, "public"); ASSERT_EQ(myVec[6].second, 1);
	ASSERT_EQ(myVec[7].first, "methods"); ASSERT_EQ(myVec[7].second, 1);
	ASSERT_EQ(myVec[8].first, "this"); ASSERT_EQ(myVec[8].second, 1);
	ASSERT_EQ(myVec[9].first, "has"); ASSERT_EQ(myVec[9].second, 1);
	ASSERT_EQ(myVec[10].first, "a"); ASSERT_EQ(myVec[10].second, 1);
	ASSERT_EQ(myVec[11].first, "total"); ASSERT_EQ(myVec[11].second, 1);
	ASSERT_EQ(myVec[12].first, "of"); ASSERT_EQ(myVec[12].second, 1);
	ASSERT_EQ(myVec[13].first, "twentytwo"); ASSERT_EQ(myVec[13].second, 1);
	ASSERT_EQ(myVec[14].first, "words"); ASSERT_EQ(myVec[14].second, 2);
	ASSERT_EQ(myVec[15].first, "but"); ASSERT_EQ(myVec[15].second, 1);
	ASSERT_EQ(myVec[16].first, "nineteen"); ASSERT_EQ(myVec[16].second, 1);
	ASSERT_EQ(myVec[17].first, "are"); ASSERT_EQ(myVec[17].second, 1);
	ASSERT_EQ(myVec[18].first, "unique"); ASSERT_EQ(myVec[18].second, 1);
	
}

