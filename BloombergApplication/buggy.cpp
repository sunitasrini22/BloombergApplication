#include "buggy.h"


static Word s_word;


// Worker thread: consume words passed from the main thread and insert them
// in the 'word list' (s_wordsArray), while removing duplicates. Terminate when
// the word 'end' is encountered.
static void workerThread(WordArray * arr)
{
	bool endEncountered = false;
	bool found = false;
	while (!endEncountered)
	{
		if (s_word.data[0]) // Do we have a new word?
		{
			//trying to eliminate the \n from the end of the string
			int pos = s_word.data.find("\n");
			if(pos>-1)
				s_word.data.replace(pos, 2, "");
			Word * w = new Word(s_word); // Copy the word
			s_word.data[0] = 0; // Inform the producer that we consumed the word
			string end = "end";
			endEncountered = (w->data.compare(end) == 0);
			if (!endEncountered)
			{
				// Do not insert duplicate words
				for (auto p : arr->s_wordsArray)
				{
					if (!p->data.compare(w->data))
					{
						++p->count;
						found = true;
						break;
					}
				}
				if (!found)
					arr->s_wordsArray.push_back(w);
			}

		}
	}
};

WordArray::WordArray()
	:s_totalFound(0)
{
}
// Read input words from STDIN and pass them to the worker thread for
// inclusion in the word list.
// Terminate when the word 'end' has been entered.
//
void WordArray::readInputWords()
{
	bool endEncountered = false;
	std::thread worker(workerThread, this);

	char * linebuf = new char[256];

	while (!endEncountered)
	{
		if (!fgets(linebuf, sizeof(linebuf), stdin)) // EOF?
			return;

		endEncountered = std::strcmp(linebuf, "end\n") == 0;

		s_word.data = linebuf;
		s_word.count = 1;
		// Pass the word to the worker thread
		//strcpy(s_word.data, linebuf);

		while (s_word.data[0]); // Wait for the worker thread to consume it
	}

	worker.join(); // Wait for the worker to terminate
}

//Unfortunately there is no thorough way of reproducing standard input via unit tests
//So creating a mock readInputWords function to be able to read from files instead.
void WordArray::readInputWords(string fileName)
{
	bool endEncountered = false;
	std::thread worker(workerThread, this);

	fstream inFile;
	inFile.open(fileName);
	string str;

	while ((std::getline(inFile, str)) && (!endEncountered))
	{
		endEncountered = str.compare("end\n") == 0;
		// Process str
		auto x = this;
		s_word.data = str;
		s_word.count = 1;
		// Pass the word to the worker thread
		//strcpy(s_word.data, linebuf);

		while (s_word.data[0]); // Wait for the worker thread to consume it
	}

	worker.join(); // Wait for the worker to terminate
}

// Repeatedly ask the user for a word and check whether it was present in the word list
// Terminate on EOF
//

void WordArray::lookupWords()
{
	char * linebuf = new char[32];

	for (;;)
	{
		std::printf("\nEnter a word for lookup:");
		if (std::scanf("%s", linebuf) == EOF)
			return;

		// Initialize the word to search for
		Word * w = new Word();
		w->data = linebuf;

		int i = findWord(w);
		if (i != -1)
		{
			cout << "SUCCESS: '" << s_wordsArray[i]->data << "' was present " << s_wordsArray[i]->count << " times in the initial word list" << endl;
		}
		else
		{
			cout << "'" << w->data << "' was NOT found in the initial word list" << endl;
		}
	}
}

//Again there is no way to test LookupWords entirely via unit tests since it needs std inputs
//So creating this function to be used by unit tests.
int WordArray::findWord(Word * w)
{
	// Search for the word
	unsigned i;
	for (i = 0; i < s_wordsArray.size(); ++i)
	{
		if (s_wordsArray[i]->data.compare(w->data) == 0)
		{
			++s_totalFound;
			return i;
		}
	}
	return -1;
}


bool sortFunction(Word* a, Word* b) { return (a->data < b->data); }

void WordArray::sortWords()
{
	sort(s_wordsArray.begin(), s_wordsArray.end(), sortFunction);
}


void WordArray::displayWords()
{
	cout << endl << "=== Word list:" << endl;
	for (auto p : s_wordsArray)
		cout << endl << p->data << " " << p->count;
}

int main()
{
	try
	{
		WordArray arr;
		arr.readInputWords();

		// Sort the words alphabetically
		arr.sortWords();

		// Print the word list
		arr.displayWords();

		arr.lookupWords();

		cout << endl << "=== Total words found: " << arr.getTotalWords() << endl;
	}
	catch (std::exception & e)
	{
		cout << "error " << e.what() << endl;
	}

	return 0;
}

