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

		TEST_METHOD(TestReadInputWordsFromFileAndVerifyMatchingWords)
		{
			WordArray simWord;
			simWord.readInputWords("../../ApplicationTest/Test1.txt");			

			vector<string> expectedWords;
			expectedWords.push_back("sunita");
			expectedWords.push_back("what");
			expectedWords.push_back("test");
			expectedWords.push_back("are");
			expectedWords.push_back("you");
			expectedWords.push_back("performing");
			Assert::AreEqual<int>(expectedWords.size(), simWord.s_wordsArray.size(), L"Total number of words doesn't match");
			for (int i = 0; i < expectedWords.size(); i++)
			{
				Assert::AreEqual(expectedWords[i], simWord.s_wordsArray[i]->data, L"Words read from file doesn't match expected set of words");
			}
		}

		TEST_METHOD(TestReadAndSortWordsFromFileAndVerifyMatchingWords)
		{
			WordArray simWord;
			simWord.readInputWords("../../ApplicationTest/Test1.txt");
			simWord.sortWords();
			
			vector<string> expectedWords;
			expectedWords.push_back("are");
			expectedWords.push_back("performing");
			expectedWords.push_back("sunita");			
			expectedWords.push_back("test");
			expectedWords.push_back("what");
			expectedWords.push_back("you");
			
			Assert::AreEqual<int>(expectedWords.size(), simWord.s_wordsArray.size(), L"Total number of words doesn't match");
			for (int i = 0; i < expectedWords.size(); i++)
			{
				Assert::AreEqual(expectedWords[i], simWord.s_wordsArray[i]->data, L"Words read from file doesn't match expected set of words");
			}
		}

	};
}