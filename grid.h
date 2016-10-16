#pragma once
#include <iostream>
#include <fstream>
using namespace std;

// grid class stores a word search grid in 2D char matrix
class grid
{
public:
	int rows = 0, columns = 0;
	char** matrix;
	grid();
	~grid();
	void readGrid(const string& fileName);
};

