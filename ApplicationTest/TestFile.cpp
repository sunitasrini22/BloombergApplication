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
			Assert::AreEqual(0, simWord.getTotalWords(), L"Total number of words doesn't match");
		}

		

	};
}