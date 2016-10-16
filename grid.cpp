#include "grid.h"



grid::grid()
{
}


grid::~grid()
{
}

// read grid takes in a filename and creates a 2D char array filled with the grid in the file
void grid::readGrid(const string & fileName)
{
	//open file
	fstream file;
	file.open(fileName);
	//take in row/col info
	file >> rows >> columns;
	cout << rows << " " << columns << endl;
	//declare the new matrix of rows
	matrix = new char*[rows];
	for (int i = 0; i < rows; i++)
	{
		//init column
		matrix[i] = new char[columns];
		for (int j = 0; j < columns; j++)
		{
			//fill column
			file >> matrix[i][j];
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}
