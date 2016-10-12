#include "grid.h"



grid::grid()
{
}


grid::~grid()
{
}

void grid::readGrid(const string & fileName)
{
	fstream file;
	file.open(fileName);
	file >> rows >> columns;
	cout << rows << " " << columns << endl;
	matrix = new char*[rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new char[columns];
		for (int j = 0; j < columns; j++)
		{
			file >> matrix[i][j];
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}
