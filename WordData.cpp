// Title: Lab 7 WordData class and implementation
// Author: Martin Plut
// Description: This is the header file containing the class WordData and it's prototype functions

#include "WordData.h"

WordData::WordData()
{
	word = new char [1];
	word[0] = '\0';
	length = 0;
	vowels = consonants = digits = specialchars = 0;
}

WordData::WordData(const WordData & OtherWord)
{
	word = new char [1+OtherWord.length];
	strcpy (word, OtherWord.word);
	length = OtherWord.length;
	vowels = OtherWord.vowels;
	consonants = OtherWord.consonants;
	digits = OtherWord.digits;
	specialchars = OtherWord.specialchars;
}

WordData::~WordData()
{
	if (word)
		delete [] word;
}

WordData::WordData (const string & InWord)
{
	word = new char [1];
	word = '\0';
	SetWord (InWord);
}
bool WordData::isvowel (char aletter)
{
	char upcase = toupper (aletter);
	if (upcase == 'A' || upcase == 'E' || upcase == 'I'
		|| upcase == 'O' || upcase == 'U')
			return true;
	return false;
}
void WordData::SetWord(const string & InWord)
{
	if (word)
		delete [] word;
	length = InWord.length();
	word = new char [1+length];
	strcpy(word, InWord.c_str());
	vowels = consonants = digits = specialchars = 0;
	for (int i = 0; i < strlen(word); i++)
	{
		if (isalpha(word[i]))
		{
			switch (toupper (word[i]))
			{
				case 'A': case 'E': case 'I':
				case 'O': case 'U':
					vowels++; break;
				default:
					consonants++;
			}
		}
		else if (isdigit(word[i]))
			digits++;
		else
			specialchars++;
	}
}

string WordData::GetWord() const
{
	return word;
}

void WordData::WriteData (ostream & outs) const
{
	outs << setw(12) << left << word;
	outs << setw(8) << right << vowels;
	outs << setw(8) << consonants;
	outs << setw(8) << digits;
	outs << setw(8) << specialchars << endl;
}

int WordData::GetNumVowels () const
{
	//This functions will return the integer value for the amount of vowels
	return vowels;
}

int WordData::GetNumConsonants () const
{
	//This function returns number of consonants
	return consonants;
}

int WordData::GetNumDigits () const
{
	//This function returns number of digits
	return digits;
}

int WordData::GetNumSpecialChars() const
{
	//This function returns number of special characters
	return specialchars;
	
}

bool WordData::operator < (const WordData & OtherWord) const
{
	if (length < OtherWord.length)
		return true;
	if (length > OtherWord.length)
		return false;
	string one = word;
	for (int i = 0; i < one.length(); i++)
		one[i] = tolower(one[i]);
	string two = OtherWord.word;
	for (int i = 0; i < two.length(); i++)
		two[i] = tolower(two[i]);
	return one < two;
}

bool WordData::operator > (const WordData & OtherWord) const
{
	if (length > OtherWord.length)
		return true;
	if (length < OtherWord.length)
		return false;
	string one = word;
	string two = OtherWord.word;
	for (int i = 0; i < one.length(); i++)
		one[i] = tolower(one[i]);
	for (int i = 0; i < two.length(); i++)
		two[i] = tolower(two[i]);
	return one > two; 
}

WordData & WordData::operator = (const WordData & OtherWord)
{
	// Test for self-assignment. If this and the address of OtherWord
	// are the same, return the object referenced by this
	if (this == &OtherWord)
		return * this;
	
	// Delete the exiisting word
	delete [] word;
	// Allocate space for nwew word
	word = new char [1+OtherWord.length];
	// Copy the new word from OtherWord into word
	strcpy (word, OtherWord.word);
	length = OtherWord.length;
	// Copy the attriblutes of the OtherWord int to the corresponding
	// attributes of this:
	vowels=OtherWord.vowels;
	consonants=OtherWord.consonants;
	digits=OtherWord.digits;
	specialchars=OtherWord.specialchars;
	
	// Return the object reference by this
	return * this;
}

bool WordData::operator == (const WordData & OtherWord) const
{
		if (strcmp (word, OtherWord.word) == 0)
			return true;
		return false;
}

WordData WordData::operator + (const WordData & OtherWord) const
{
	WordData sum;
	sum.length = length + OtherWord.length;
	cout << OtherWord.word << endl;
	delete [] sum.word;
	sum.word = new char [sum.length + 1];
	strcpy (sum.word, word);
	strcat (sum.word, OtherWord.word);
	sum.vowels = vowels + OtherWord.vowels;
	sum.consonants = consonants + OtherWord.consonants;
	sum.digits = digits + OtherWord.digits;
	sum.specialchars = specialchars + OtherWord.specialchars;
	return sum;
}

ostream & operator << (ostream & outs, const WordData & w)
{
	outs << setw(12) << left << w.word;
	outs << setw(8) << right << w.vowels;
	outs << setw(8) << w.consonants;
	outs << setw(8) << w.digits;
	outs << setw(8) << w.specialchars;
	return outs;
}

istream & operator >> (istream & ins, WordData & w)
{
	string astring;
	ins >> astring;
	if (!ins.fail()) //if the stream does NOT fail
		w.SetWord(astring);
	return ins;
}
