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
			Assert::AreEqual(0, (int)simWord.s_wordsArray.size(), L"Total number of words doesn't match");
		}


		TEST_METHOD(TestReadInputWordsFromFileAndCheckWordListSize)
		{
			WordArray simWord;
			simWord.readInputWords("../../ApplicationTest/TestUniqueWords.txt");			
			Assert::AreEqual(6, (int)simWord.s_wordsArray.size(), L"Total number of words doesn't match");
		}

		TEST_METHOD(TestReadInputWordsFromFileAndVerifyMatchingWords)
		{
			WordArray simWord;
			simWord.readInputWords("../../ApplicationTest/TestUniqueWords.txt");			

			vector<string> expectedWords;
			expectedWords.push_back("sunita");
			expectedWords.push_back("what");
			expectedWords.push_back("test");
			expectedWords.push_back("are");
			expectedWords.push_back("you");
			expectedWords.push_back("performing");
			Assert::AreEqual(expectedWords.size(), simWord.s_wordsArray.size(), L"Total number of words doesn't match");
			for (int i = 0; i < expectedWords.size(); i++)
			{
				Assert::AreEqual(expectedWords[i], simWord.s_wordsArray[i]->data, L"Words read from file doesn't match expected set of words");
			}
		}

		TEST_METHOD(TestReadAndSortWordsFromFileAndVerifyMatchingWords)
		{
			WordArray simWord;
			simWord.readInputWords("../../ApplicationTest/TestUniqueWords.txt");
			simWord.sortWords();
			
			vector<string> expectedWords;
			expectedWords.push_back("are");
			expectedWords.push_back("performing");
			expectedWords.push_back("sunita");			
			expectedWords.push_back("test");
			expectedWords.push_back("what");
			expectedWords.push_back("you");
			
			Assert::AreEqual(expectedWords.size(), simWord.s_wordsArray.size(), L"Total number of words doesn't match");
			for (int i = 0; i < expectedWords.size(); i++)
			{
				Assert::AreEqual(expectedWords[i], simWord.s_wordsArray[i]->data, L"Words read from file doesn't match expected set of words");
			}
		}

		TEST_METHOD(TestReadFromFileAndLookupWords)
		{
			WordArray simWord;
			simWord.readInputWords("../../ApplicationTest/TestUniqueWords.txt");
			Word* w = new Word("performing");
			Assert::AreEqual(0, simWord.getTotalWords(), L"Total found words should be 0");
			simWord.findWord(w);
			Assert::AreEqual(1, simWord.getTotalWords(), L"Total found words should be 1");

		}

		TEST_METHOD(TestReadFromFileAndLookupWordsNonExistent)
		{
			WordArray simWord;
			simWord.readInputWords("../../ApplicationTest/TestUniqueWords.txt");
			Word* w = new Word("can");
			Assert::AreEqual(0, simWord.getTotalWords(), L"Total found words should be 0");
			simWord.findWord(w);
			Assert::AreEqual(0, simWord.getTotalWords(), L"Total found words should be 0");

		}

		TEST_METHOD(TestLookupWordsNonExistent)
		{
			WordArray simWord;
			simWord.readInputWords("../../ApplicationTest/TestUniqueWords.txt");
			Word* w = new Word("can");
			int i = simWord.findWord(w);
			Assert::AreEqual<int>(-1, i, L"index returned by findWord should be -1 since the word is not found.");

		}

		TEST_METHOD(TestLookupWordsForMatchingCount)
		{
			WordArray simWord;
			simWord.readInputWords("../../ApplicationTest/TestUniqueWords.txt");
			Word* w = new Word("performing");
			int i = simWord.findWord(w);
			Assert::IsTrue(i > -1, L"The index returned from findWord should be greater than -1");
			Assert::AreEqual<int>(1, simWord.s_wordsArray[i]->count, L"Count of words found should be 1");

		}

		TEST_METHOD(TestRepeatingWords)
		{
			WordArray simWord;
			simWord.readInputWords("../../ApplicationTest/TestRepeatingWords.txt");
			Word* w = new Word("you");
			int i = simWord.findWord(w);
			Assert::IsTrue(i > -1, L"The index returned from findWord should be greater than -1");
			Assert::AreEqual<int>(2, simWord.s_wordsArray[i]->count, L"The word you should have appeared twice");

			w->data = "can";
			i = simWord.findWord(w);
			Assert::IsTrue(i > -1, L"The index returned from findWord should be greater than -1");
			Assert::AreEqual(1, simWord.s_wordsArray[i]->count, L"The word can should have appeared once");

		}

		TEST_METHOD(TestEmptyInputFile)
		{
			WordArray simWord;
			simWord.readInputWords("../../ApplicationTest/TestBlank.txt");

			Assert::AreEqual(0, (int)simWord.s_wordsArray.size(), L"Total number of words should be 0 since the file is blank");
			Word* w = new Word("you");
			int i = simWord.findWord(w);
			Assert::AreEqual(-1, i, L"The index returned from findWord should be -1 since no words are present");

		}


		TEST_METHOD(TestLongInputFile)
		{
			WordArray simWord;
			simWord.readInputWords("../../ApplicationTest/TestLong.txt");

			//This file is a collection of 5 long sentences repeating 7 times, so the total number of words would still be 5
			Assert::AreEqual(5, (int)simWord.s_wordsArray.size(), L"Total number of words should be 0 since the file is blank");
			Word* w = new Word("khsbfvhbsdfhvbsdfvbhskdjbjksfngkdfkb skfjgbkjnsfkjbgnfgglndsb");
			int i = simWord.findWord(w);
			Assert::IsTrue(i > -1, L"The index returned from findWord should be greater than -1");
			Assert::AreEqual(7, (int)simWord.s_wordsArray[i]->count, L"The word can should have appeared 7 times");

		}
	};
}