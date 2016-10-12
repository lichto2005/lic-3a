#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class grid
{
public:
	int rows = 0, columns = 0;
	char** matrix;
	grid();
	~grid();
	void readGrid(const string& fileName);
};

