#pragma once
#include <iostream>
#include<string>
#include <fstream>
using namespace std;

namespace MyLib
{

	void PrintFileContenet(string FileName)
	{
		fstream MyFile;
		MyFile.open(FileName, ios::in);//Read Mode.

		if (MyFile.is_open())
		{

			string line;

			while (getline(MyFile, line))
			{
				cout << line << endl;
			}
			MyFile.close();
		}
	}


	void ReadArray(int Array[], int length)
	{
		Array[length];
		for (int i = 0; i < length; i++)
		{
			cout << "Enter element [" << i + 1 << "] : ";
			cin >> Array[i];
		}
	}


	int RandomNumber(int from, int to)
	{
		return rand() % (to - from + 1) + from;
	}


	int ReadNumber(string Message)
	{
		int Number;
		cout << Message;
		cin >> Number;
		return Number;
	}


}
