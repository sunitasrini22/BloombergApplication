Assumptions made:
-This program starts with nothing displayed on the console. A blank console shows up since nothing about that was specifically mentioned in the problem statement.
-The input needs to be a word or sentence per line.
-Each of these words is added into the list of words passed in until the word end is encountered
-end is not added to the list of words.
-end needs to be added as its own line not as part of another word.

The TestFile.cpp has unit tests that test out some cases. Unfortunately since the problem statement needs input sent in from standard input, there's no way to do 
that using unit tests hence some portions of the code could not be reached via tests but they have been tested manually. I had to also mock some portions of the
code to read input from files instead of the console. These test files are also part of the same package. 

Here is a typical test case run via the console:
this
is
just
a
sample
test
test
test
end

=== Word list:

a 1
is 1
just 1
sample 1
test 3
this 1
Enter a word for lookup:test
SUCCESS: 'test' was present 3 times in the initial word list

Enter a word for lookup:not
'not' was NOT found in the initial word list

Enter a word for lookup:^Z

=== Total words found: 1

