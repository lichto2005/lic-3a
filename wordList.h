#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//wordlist stores a list of words with methods to sort them
class wordList
{
public:
	vector<string> words;
	wordList();
	~wordList();
	void readWords(const string& fileName);
	friend ostream& operator<<(ostream& os, const wordList& wl);
	void sortInsertion();
	void sortQuick(int left, int right);
	void merge(int left, int middle, int right);
	void sortMerge(int left, int right);
	bool inList(string word);
	void sortHeap();
};

