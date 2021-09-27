/*****************************************************************
 * Project: Project 4
 * File: Project4.cpp
 * Author: Martin Plut
 * Date: December 12th, 2017
 * Description: File for testing OrderedSet and WordData Class   */
#include <iostream>
#include <fstream>
#include "OrderedSet.hpp"
#include "WordData.h"
#include "WordData.cpp"
using namespace std;

int WordDataTest (string file);
int IntTest();

int IntTest()
{
	OrderedSet<int> IS;
	IS.Insert(10);
	IS.Insert(7);
	IS.Insert(5);
	IS.Insert(0);
	IS.Insert(-1);
	IS.Insert(-4);
	IS.Insert(-5);
	IS.SetDirection(BACKWARD);
	IS.Delete(0);
	IS.Delete(-4);
	IS.Delete(-5);
	IS.Delete(10);
	IS.Delete(7);
	cout << "Elements in IS: " << IS << endl;
	return 0;
}
int main()
{
	//WordDataTest ("words.txt");
	IntTest();
	return 0;
}

int WordDataTest (string file)
{
	cout << "Testing OrderedSet with WordData:\n\n";
	ifstream input (file.c_str());
	WordData oneword;
	OrderedSet<WordData> WD;
	while (input >> oneword)
		WD.Insert(oneword);	
	input.close();
	OrderedSet<WordData>::Iterator itr;
	cout << "From first to last:\n";
	for (itr = WD.begin(); itr != WD.end(); itr++)
		cout << '\t' << *itr << endl;
	cout << "From last to first:\n";
	for (itr = WD.rbegin(); itr != WD.rend(); --itr)
		cout << '\t' << *itr << endl;
	cout << "End of OrderedSet with WordData test\n\n";
	return 0;
}
