#include <thread>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>

using namespace std;
struct Word
{
	string data;
	int count;

	Word(string data_) :
		data(data_),
		count(1)
	{}

	Word() :
		data(""),
		count(0)
	{}
};

class WordArray
{
public:
	WordArray();
	void readInputWords();
	void readInputWords(string fileName);
	void lookupWords();
	void sortWords();
	void displayWords();
	int findWord(Word* w);
	int getTotalWords() {
		return s_totalFound;
	};
	//bool myfunction(Word a, Word b);
	//void workerThread();
	//private:
	std::vector<Word*> s_wordsArray;
	int s_totalFound;
};
