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
	void workerThread();
	int getWordArraySize() { return (int)s_wordsArray.size(); }
	vector<Word*> getWords() { return s_wordsArray; }
private:
	std::vector<Word*> s_wordsArray;
	int s_totalFound;
};
