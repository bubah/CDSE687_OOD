#include "pch.h"
#include "C:/CSE687/Dev/MapReduce/MapReduce/Map.cpp"
#include "C:/CSE687/Dev/MapReduce/MapReduce/FileManagement.cpp"
#include "C:/CSE687/Dev/MapReduce/MapReduce/Sort.cpp"

struct InputFileMethodsTest : public testing::Test {
	FileManagement *fm;
	void SetUp() {
		fm = new FileManagement("C:\\CSE687\\Dev\\MapReduce\\MapReduce\\InputDir", "C:\\CSE687\\Dev\\MapReduce\\MapReduce\\TempDir");
		fs::directory_iterator inputDir_Itr{ "C:\\CSE687\\Dev\\MapReduce\\MapReduce\\InputDir" }; // pointer to first file in interm directory
		fs::path tempFile_Path{ *inputDir_Itr }; // path to first file in interm directory
		fs::ofstream ofs{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
		ofs.close(); // Close file
	}
	void TearDown() {
		delete fm;
	}
};
struct TempFileMethodsTest : public testing::Test {
	FileManagement *fm;
	void SetUp() {
		fm = new FileManagement("C:\\CSE687\\Dev\\MapReduce\\MapReduce\\InputDir", "C:\\CSE687\\Dev\\MapReduce\\MapReduce\\TempDir");
		fs::directory_iterator tempDir_Itr{ "C:\\CSE687\\Dev\\MapReduce\\MapReduce\\TempDir" }; // pointer to first file in interm directory
		fs::path tempFile_Path{ *tempDir_Itr }; // path to first file in interm directory
		fs::ofstream ofs{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
		ofs.close(); // Close file
	}
	void TearDown() {
		delete fm;
	}
};
TEST(MapTest, TestMapperOnEmptyData) {
	//Arrange
	fs::directory_iterator tmpDir_Itr{ "C:\\CSE687\\Dev\\MapReduce\\MapReduce\\TempDir" }; // pointer to first file in interm directory
	fs::path tempFile_Path{ *tmpDir_Itr }; // path to first file in interm directory
	fs::ofstream ofs{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
	ofs.close(); // Close file
	FileManagement fm("C:\\CSE687\\Dev\\MapReduce\\MapReduce\\InputDir", "C:\\CSE687\\Dev\\MapReduce\\MapReduce\\TempDir");
	Map mp;
	mp.mapper(fm.getInputFileName(), "", fm.getTmpFileName(), fm);

	//Act
	string tmpFileContent = fm.readFromTmpFile(fm.getTmpFileName());

	//Assert
	ASSERT_STREQ(tmpFileContent.c_str(), "");
}

TEST(MapTest, TestMapperOneWordToken) {
	//Arrange
	fs::directory_iterator tmpDir_Itr{ "C:\\CSE687\\Dev\\MapReduce\\MapReduce\\TempDir" }; // pointer to first file in interm directory
	fs::path tempFile_Path{ *tmpDir_Itr }; // path to first file in interm directory
	fs::ofstream ofs{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
	ofs.close(); // Close file
	FileManagement fm("C:\\CSE687\\Dev\\MapReduce\\MapReduce\\InputDir", "C:\\CSE687\\Dev\\MapReduce\\MapReduce\\TempDir");
	Map mp;
	mp.mapper(fm.getInputFileName(), "*oneword&#", fm.getTmpFileName(), fm);

	//Act
	string tmpFileContent = fm.readFromTmpFile(fm.getTmpFileName());

	//Assert
	ASSERT_STREQ(tmpFileContent.c_str(), "oneword,1 ");
}

TEST(MapTest, TestMapperTwoWordToken) {
	//Arrange
	fs::directory_iterator tmpDir_Itr{ "C:\\CSE687\\Dev\\MapReduce\\MapReduce\\TempDir" }; // pointer to first file in interm directory
	fs::path tempFile_Path{ *tmpDir_Itr }; // path to first file in interm directory
	fs::ofstream ofs{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
	ofs.close(); // Close file
	FileManagement fm("C:\\CSE687\\Dev\\MapReduce\\MapReduce\\InputDir", "C:\\CSE687\\Dev\\MapReduce\\MapReduce\\TempDir");
	Map mp;
	mp.mapper(fm.getInputFileName(), "*two&#! words()", fm.getTmpFileName(), fm);

	//Act
	string tmpFileContent = fm.readFromTmpFile(fm.getTmpFileName());

	//Assert
	ASSERT_STREQ(tmpFileContent.c_str(), "two,1 words,1 ");
}

TEST(MapTest, TestMapperAllCharacters) {
	//Arrange
	fs::directory_iterator tmpDir_Itr{ "C:\\CSE687\\Dev\\MapReduce\\MapReduce\\TempDir" }; // pointer to first file in interm directory
	fs::path tempFile_Path{ *tmpDir_Itr }; // path to first file in interm directory
	fs::ofstream ofs{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
	ofs.close(); // Close file
	FileManagement fm("C:\\CSE687\\Dev\\MapReduce\\MapReduce\\InputDir", "C:\\CSE687\\Dev\\MapReduce\\MapReduce\\TempDir");
	Map mp;
	mp.mapper(fm.getInputFileName(), "~`!@#$%^&*()-_=+{}[]:;'<>,.?/|\ ", fm.getTmpFileName(), fm);

	//Act
	string tmpFileContent = fm.readFromTmpFile(fm.getTmpFileName());

	//Assert
	ASSERT_STREQ(tmpFileContent.c_str(), "");
}

TEST_F(InputFileMethodsTest, TestRead_WriteToInput) {
	//Act
	string fileName_Str = fm->getInputFileName();
	fm->writeToInputFile(fileName_Str, "Testing One two three");

	//Assert
	ASSERT_EQ(fm->readFromInputFile(fileName_Str), "Testing One two three ");
}

TEST_F(InputFileMethodsTest, TestGetInputFileName) {
	//Assert
	ASSERT_EQ(fm->getInputFileName(), "C:\\CSE687\\Dev\\MapReduce\\MapReduce\\InputDir\\InputFile1.txt");
}

TEST_F(InputFileMethodsTest, TestIncrementInputFilePointer) {
	//Act
	ASSERT_EQ(fm->getInputFileName(), "C:\\CSE687\\Dev\\MapReduce\\MapReduce\\InputDir\\InputFile1.txt");
	fm->incrementInputFilePointer();
	ASSERT_EQ(fm->getInputFileName(), "C:\\CSE687\\Dev\\MapReduce\\MapReduce\\InputDir\\InputFile2.txt");
}

TEST_F(TempFileMethodsTest, TestwriteToTmpFile_Str) {
	//Act
	
	fm->writeToTmpFile(fm->getTmpFileName(), "map reduce project");

	//Assert
	ASSERT_EQ(fm->readFromTmpFile(fm->getTmpFileName()), "map reduce project ");

}

TEST_F(TempFileMethodsTest, TestwriteToTmpFile_Vec) {
	//Act
	vector<string> myVector{ "my", "name", "is" , "john", "doe" };
	fm->writeToTmpFile(fm->getTmpFileName(), myVector);

	//Assert
	ASSERT_EQ(fm->readFromTmpFile(fm->getTmpFileName()), "my name is john doe ");

}

TEST(SortClassTest, TestSortDataMethod) {
	//Arrange
	Sort Sd("my name is john doe");

	//Act
	Sd.SortData();
	vector<string> vec = Sd.exportSortedData();

	//Assert
	ASSERT_EQ(vec[0], "doe");
	ASSERT_EQ(vec[1], "is");
	ASSERT_EQ(vec[2], "john");
	ASSERT_EQ(vec[3], "my");
	ASSERT_EQ(vec[4], "name");
}

