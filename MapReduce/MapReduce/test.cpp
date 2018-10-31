#include "pch.h"

#include "../MapReduce/Map.cpp"
#include "../MapReduce/FileManagement.cpp"
#include "../MapReduce/Sort.cpp"


TEST(MAPTEST, mytest) {
	ASSERT_EQ(1, 1);
}


TEST(MapTest, TestMapper_ExportOnEmptyData) {
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

TEST(MapTest, TestMapper_ExportOneWordToken) {
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


TEST(MapTest, TestMapper_ExportTwoWordToken) {
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

TEST(MapTest, TestMapper_ExportAllCharacters) {
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


TEST(FileMgrTest, Test_Constr_getterfunctions) {
	FileManagement fm("C:\\testInput", "C:\\testTemp", "C:\\testOutput");

	fs::path inPath = fm.getInputDir();

	fs::path tmpPath = fm.getTempDir();

	ASSERT_EQ(inPath, "C:\\testInput");
	ASSERT_EQ(tmpPath, "C:\\testTemp");

}

/*TEST(InputFileMethodsTest1, TestGetInputFileName) {
	FileManagement fm("C:\\testInput", "C:\\testTemp");
	fs::directory_iterator inputDir_Itr{ "C:\\testInput" };
	fs::path inputFile_Path{ *inputDir_Itr };
	fs::ofstream ofs{ inputFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
	ofs.close(); // Close file


	//Assert
	ASSERT_EQ(fm.getInputFileName(), "input.txt");
}

/*struct InputFileMethodsTest : public testing::Test {
	FileManagement *fm;
	void SetUp() {
		fm = new FileManagement("C:\\Users\\conte\\Documents\\GitHub\\CDSE687_OOD\\MapReduce\\MapReduce\i", "C:\\Users\\conte\\Documents\\GitHub\\CDSE687_OOD\\MapReduce\\MapReduce\\t");
		fs::directory_iterator inputDir_Itr{ "C:\\Users\\conte\\Documents\\GitHub\\CDSE687_OOD\\MapReduce\\MapReduce\i" }; // pointer to first file in interm directory
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
		fm = new FileManagement("C:\\Users\\conte\\Documents\\GitHub\\CDSE687_OOD\\MapReduce\\MapReduce\i", "C:\\Users\\conte\\Documents\\GitHub\\CDSE687_OOD\\MapReduce\\MapReduce\\t");
		fs::directory_iterator tempDir_Itr{ "C:\\Users\\conte\\Documents\\GitHub\\CDSE687_OOD\\MapReduce\\MapReduce\t" }; // pointer to first file in interm directory
		fs::path tempFile_Path{ *tempDir_Itr }; // path to first file in interm directory
		fs::ofstream ofs{ tempFile_Path, std::ofstream::out | std::ofstream::trunc };  //Opens temp file and Clears content
		ofs.close(); // Close file
	}
	void TearDown() {
		delete fm;
	}
};



TEST_F(InputFileMethodsTest, TestRead_WriteToInput) {
	//Act
	string fileName_Str = fm->getInputFileName();
	fm->writeToInputFile(fileName_Str, "Testing One two three");

	//Assert
	ASSERT_EQ(fm->readFromInputFile(fileName_Str), "Testing One two three ");
}

TEST_F(InputFileMethodsTest, TestGetInputFileName) {
	//Assert
	ASSERT_EQ(fm->getInputFileName(), "C:\\Users\\conte\\Documents\\GitHub\\CDSE687_OOD\\MapReduce\\MapReduce\i\\Input.txt");
}

TEST_F(InputFileMethodsTest, TestIncrementInputFilePointer) {
	//Act
	ASSERT_EQ(fm->getInputFileName(), "C:\\Users\\conte\\Documents\\GitHub\\CDSE687_OOD\\MapReduce\\MapReduce\i\\Input.txt");
	fm->incrementInputFilePointer();
	ASSERT_EQ(fm->getInputFileName(), "C:\\Users\\conte\\Documents\\GitHub\\CDSE687_OOD\\MapReduce\\MapReduce\i\\Input.txt");
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
}*/