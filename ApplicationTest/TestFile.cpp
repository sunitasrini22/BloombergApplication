#include "stdafx.h"
#include "CppUnitTest.h"
#include "../BloombergApplication/buggy.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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

		TEST_METHOD(TestReadFromFileAndLookupWords)
		{
			WordArray simWord;
			simWord.readInputWords("../../ApplicationTest/Test1.txt");
			Word* w = new Word("performing");
			Assert::AreEqual(0, simWord.getTotalWords(), L"Total found words should be 0");
			simWord.findWord(w);
			Assert::AreEqual(1, simWord.getTotalWords(), L"Total found words should be 1");

		}

		TEST_METHOD(TestReadFromFileAndLookupWordsNonExistent)
		{
			WordArray simWord;
			simWord.readInputWords("../../ApplicationTest/Test1.txt");
			Word* w = new Word("can");
			Assert::AreEqual(0, simWord.getTotalWords(), L"Total found words should be 0");
			simWord.findWord(w);
			Assert::AreEqual(0, simWord.getTotalWords(), L"Total found words should be 0");

		}

		TEST_METHOD(TestLookupWordsNonExistent)
		{
			WordArray simWord;
			simWord.readInputWords("../../ApplicationTest/Test1.txt");
			Word* w = new Word("can");
			int i = simWord.findWord(w);
			Assert::AreEqual<int>(-1, i, L"index returned by findWord should be -1 since the word is not found.");

		}

		TEST_METHOD(TestLookupWordsForMatchingCount)
		{
			WordArray simWord;
			simWord.readInputWords("../../ApplicationTest/Test1.txt");
			Word* w = new Word("performing");
			int i = simWord.findWord(w);
			Assert::IsTrue(i > -1, L"The index returned from findWord should be greater than -1");
			Assert::AreEqual<int>(1, simWord.s_wordsArray[i]->count, L"Count of words found should be 1");

		}

	};
}