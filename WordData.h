// Title: Lab 7 WordData Class
// Author: Martin Plut
// Description: This is the header file containing the class WordData

#ifndef WORDDATA
#define WORDDATA
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class WordData
{
	public:
		WordData ();
		WordData (const WordData & OtherWord);
		~WordData ();
		WordData (const string & InWord);
		bool isvowel(char aletter);
		void SetWord (const string & InWord);
		string GetWord () const;
		void WriteData (ostream & outs) const;
		int GetNumVowels () const;
		int GetNumConsonants () const;
		int GetNumDigits () const;
		int GetNumSpecialChars () const;
		bool operator < (const WordData & OtherWord) const;
		bool operator > (const WordData & OtherWord) const;
		WordData & operator = (const WordData & OtherWord);
		bool operator == (const WordData & OtherWord) const;
		WordData operator + (const WordData & OtherWord) const;
		friend istream & operator >> (istream & ins, WordData & w);
		friend ostream & operator << (ostream & outs, const WordData & w);
	private:
		//string word; // C++ string to hold the word
		char * word; // C-Style string 
		int length; 
		int vowels; // vowel counter
		int consonants; // consonant counter
		int digits; // digit counter
		int specialchars; // special character count
};
	
#endif
