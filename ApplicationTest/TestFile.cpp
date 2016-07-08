#include "stdafx.h"
#include "CppUnitTest.h"
#include "../BloombergApplication/buggy.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
/*
class SimWordArray : public WordArray
{
public:
	SimWordArray();
	void readInputWords();
	WordArray* warray;
};

void SimWordArray::readInputWords()
{

}*/

namespace ApplicationTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestGetTotalWordsForEmptyWordArray)
		{

			WordArray simWord;
			Assert::AreEqual<int>(0, simWord.s_wordsArray.size(), L"Total number of words doesn't match");
		}


		TEST_METHOD(TestReadInputWordsFromFileAndCheckWordListSize)
		{
			WordArray simWord;
			simWord.readInputWords("../../ApplicationTest/Test1.txt");			
			Assert::AreEqual<int>(6, simWord.s_wordsArray.size(), L"Total number of words doesn't match");
		}

	};
}