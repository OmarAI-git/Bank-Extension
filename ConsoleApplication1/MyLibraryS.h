#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

namespace MyLibS
{

	string ReadString(string Message)
	{
		string word;
		cout << Message;
		getline(cin >> ws, word);
		return word;
	}


	char ReadCharacter(string Message)
	{
		char letter;
		cout << Message;
		cin >> letter;
		return letter;
	}


	char InvertCharcter(char letter)
	{
		return isupper(letter) ? tolower(letter) : toupper(letter);
	}


	string InvertAllCharacter(string name)
	{
		for (int i = 0; i < name.length(); i++)
		{
			name[i] = isupper(name[i]) ? tolower(name[i]) : toupper(name[i]);
		}
		return name;
	}


	short CountUpperLetter(string name)
	{
		short count = 0;
		for (short i = 0; i < name.length(); i++)
		{
			if (isupper(name[i]))
				count++;
		}
		return count;

	}


	short CountLowerLetter(string name)
	{
		short count = 0;
		for (short i = 0; i < name.length(); i++)
		{
			if (islower(name[i]))
				count++;
		}
		return count;
	}


	short CountCharacter(string name, char letter, bool matchCase)
	{
		short count = 0;
		for (short i = 0; i < name.length(); i++)
		{
			if (matchCase)
			{
				if (name[i] == letter)
				{
					count++;
				}
			}
			else
			{
				if (tolower(name[i]) == tolower(letter))
				{
					count++;
				}
			}
		}
		return count;
	}


	bool IsVowel(char letter)
	{
		letter = tolower(letter);
		return (letter == 'a' || letter == 'o' || letter == 'u' || letter == 'e' || letter == 'i');
	}


	string JoinString(vector <string> vS, string Punctuation)
	{
		string joinString = "";

		for (string& S : vS)
		{
			joinString = joinString + S + Punctuation;
		}

		return joinString.substr(0, joinString.length() - Punctuation.length());

	}


	string JoinString(string arr[], short length, string Punctuation)
	{
		string joinString = "";
		for (short i = 0; i < length; i++)
		{
			joinString = joinString + arr[i] + Punctuation;
		}
		return joinString.substr(0, joinString.length() - Punctuation.length());
	}


	vector <string> SpiltFunction(string S1, string delimiter)
	{
		vector <string> spilt;
		string sWord;
		short pos = 0;

		cout << endl << endl;
		// use find() function to get the position of the delimiter
		while ((pos = S1.find(delimiter)) != std::string::npos)
		{
			sWord = S1.substr(0, pos);

			if (sWord != delimiter)
			{
				spilt.push_back(sWord);
			}

			S1.erase(0, pos + delimiter.length());// erase() until position and move to next word
		}

		if (S1 != delimiter)
		{
			spilt.push_back(S1);// it adds last word of the string
		}

		return spilt;
	}
}