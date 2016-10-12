#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


class wordList
{
private:
	vector<string> words;
public:
	wordList();
	~wordList();
	void readWords(const string& fileName);
	friend ostream& operator<<(ostream& os, const wordList& wl);
	void sortInsertion();
	void sortQuick(int left, int right);
	void merge(int left, int middle, int right);
	void sortMerge(int left, int right);
	int hasWord(string word);
};

