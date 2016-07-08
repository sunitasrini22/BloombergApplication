#include <thread>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
struct Word
{
	char * data;
	int count;

	Word(char * data_) :
		data(::_strdup(data_))
	{}

	Word() :
		data((char *)"")
	{}
};

static std::vector<Word*> s_wordsArray;
static Word s_word;
static int s_totalFound;


// Worker thread: consume words passed from the main thread and insert them
// in the 'word list' (s_wordsArray), while removing duplicates. Terminate when
// the word 'end' is encountered.
static void workerThread()
{
	bool endEncountered = false;
	bool found = false;

	while (!endEncountered)
	{
		if (s_word.data[0]) // Do we have a new word?
		{
			Word * w = new Word(s_word); // Copy the word

			s_word.data[0] = 0; // Inform the producer that we consumed the word

			endEncountered = std::strcmp(s_word.data, "end") == 0;

			if (!endEncountered)
			{
				// Do not insert duplicate words
				for (auto p : s_wordsArray)
				{
					if (!std::strcmp(p->data, w->data))
					{
						++p->count;
						found = true;
						break;
					}
				}

				if (!found)
					s_wordsArray.push_back(w);
			}
		}
	}
};

// Read input words from STDIN and pass them to the worker thread for
// inclusion in the word list.
// Terminate when the word 'end' has been entered.
//
static void readInputWords()
{
	bool endEncountered = false;

	std::thread * worker = new std::thread(workerThread);

	char * linebuf = new char[32];

	while (!endEncountered)
	{
		if (!std::fgets(linebuf,sizeof(linebuf),stdin)) // EOF?
			return;

		endEncountered = std::strcmp(linebuf, "end") == 0;

		// Pass the word to the worker thread
		std::strcpy(s_word.data, linebuf);
		while (s_word.data[0]); // Wait for the worker thread to consume it
	}

	worker->join(); // Wait for the worker to terminate
}

// Repeatedly ask the user for a word and check whether it was present in the word list
// Terminate on EOF
//
static void lookupWords()
{
	bool found;
	char * linebuf = new char[32];

	for (;;)
	{
		cout<<endl<<"Enter a word for lookup:";
		if (std::scanf("%s", linebuf) == EOF)
			return;

		// Initialize the word to search for
		Word * w = new Word();
		std::strcpy(w->data, linebuf);

		// Search for the word
		unsigned i;
		for (i = 0; i < s_wordsArray.size(); ++i)
		{
			if (std::strcmp(s_wordsArray[i]->data, w->data) == 0)
			{
				found = true;
				break;
			}
		}

		if (found)
		{
			cout<<"SUCCESS: '"<< s_wordsArray[i]->data<<"' was present "<< s_wordsArray[i]->count <<" times in the initial word list"<<endl;
			++s_totalFound;
		}
		else
			cout<< w->data<<" was NOT found in the initial word list"<<endl;
	}
}

int main()
{
	try
	{
		readInputWords();

		// Sort the words alphabetically
		sort(s_wordsArray.begin(), s_wordsArray.end());

		// Print the word list
		cout<<endl<<"=== Word list:"<<endl;
		for (auto p : s_wordsArray)
			cout<<p->data<<" "<<p->count<<endl;

		lookupWords();

		cout << endl << "=== Total words found: " << s_totalFound << endl;
	}
	catch (std::exception & e)
	{
		cout<<"error "<<e.what()<<endl;
	}

	return 0;
}

