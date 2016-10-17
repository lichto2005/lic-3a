//created in Visual Studio using Windows PC
#include "wordList.h"
#include "grid.h"
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

//declare global functions
void findMatches(wordList wl, grid g);
void search(int algorithm);

//program start
int main()
{
	cout << "Heap Sort\nType grid file name: ";
	search(3);
	// cout sort type, search with proper search parameter
	cout << "Merge Sort\nType grid file name: ";
	search(0);
	cout << "Quick Sort\nType grid file name: ";
	search(1);
	cout << "Insertion Sort\nType grid file name: ";
	search(2);
	return 0;
}

// function to find matches from wl in g
void findMatches(wordList wl, grid g)
{
	cout << "---- FOUND WORDS ----\n";
	//for each letter in the grid
	for (int i = 0; i < g.rows * g.columns; i++)
	{
		// use math to find out row/col
		int col = i % g.columns;
		int row = i / g.columns;
		string s_forward;
		string s_up;
		// try each length of word up to wordlen
		for (int len = 0; len < g.columns; len++)
		{
			// concat a string with the next letter to the right
			s_forward = s_forward + (g.matrix[row][(col + len) % g.columns]);
			// see if it matches a word
			if (wl.hasWord(s_forward) != -1 && s_forward.length() >= 5)
			{
				cout << s_forward << endl;
			}
			// check from right to left by reversing string
			string s_backward = string(s_forward.rbegin(), s_forward.rend());
			// see if it matches a word
			if (wl.hasWord(s_backward) != -1 && s_backward.length() >= 5)
			{
				cout << s_backward << endl;
			}

			// concat a string with the next letter up
			s_up = s_up + (g.matrix[(row + len) % g.rows][col]);
			// see if it matches a word
			if (wl.hasWord(s_up) != -1 && s_up.length() >= 5)
			{
				cout << s_up << endl;
			}
			// check the down direction by reversing string
			string s_down = string(s_up.rbegin(), s_up.rend());
			// see if it matches a word
			if (wl.hasWord(s_down) != -1 && s_down.length() >= 5)
			{
				cout << s_down << endl;
			}
		}

		// declare index of row/col
		int j = row, k = col;
		// search up/right diag and down/left diag
		string s_up_right;
		do
		{
			// concat the next letter
			s_up_right += g.matrix[j][k];
			// check if word
			if (wl.hasWord(s_up_right) != -1 && s_up_right.length() >= 5)
			{
				cout << s_up_right << endl;
			}
			// reverse string to check down-left
			string s_down_left = string(s_up_right.rbegin(), s_up_right.rend());
			// check if word
			if (wl.hasWord(s_down_left) != -1 && s_down_left.length() >= 5)
			{
				cout << s_down_left << endl;
			}

			// move to the next letter up and to the right
			j--;
			k++;

			// if the move has put the index out of bounds
			// fix the index
			if (j < 0)
			{
				j = g.rows - 1;
			}
			if (k > g.columns - 1)
			{
				k = 0;
			}

		// add letters until you reach the first letter again
		} while (j != row && k != col);

		//redeclare the indices for down-right and up-left
		j = row, k = col;
		string s_down_right;
		do
		{
			//add the next letter
			s_down_right += g.matrix[j][k];
			//check if word
			if (wl.hasWord(s_down_right) != -1 && s_down_right.length() >= 5)
			{
				cout << s_down_right << endl;
			}
			//reverse string to check up-left
			string s_up_left = string(s_down_right.rbegin(), s_down_right.rend());
			//check if word
			if (wl.hasWord(s_up_left) != -1 && s_up_left.length() >= 5)
			{
				cout << s_up_left << endl;
			}

			//advance to next letter
			j++;
			k++;

			//fix index if out of bounds
			if (j > g.rows - 1)
			{
				j = 0;
			}

			if (k > g.columns - 1)
			{
				k = 0;
			}

		//repeat until you hit the first letter again
		} while (j != row && k != col);
	}
}

// function that handles the skeleton of the searching
void search(int algorithm)
{
	//read in a filename for the grid
	string fileName;
	cin >> fileName;
	grid g;
	g.readGrid(fileName);
	//open wordlist
	wordList wl;
	wl.readWords("wordlist2.txt");
	clock_t begin = clock();
	// sort based on parameter
	switch (algorithm)
	{
	case 3:
		wl.sortHeap();
		break;
	case 2:
		wl.sortInsertion();
		break;
	case 1:
		wl.sortQuick(0, -1);
		break;
	case 0:
		wl.sortMerge(0, -1);
		break;
	default:
		cerr << "Invalid algorithm choice. Choose [0,2]\n";
		throw exception("Invalid algorith, choice. Choose [0,2]\n");
	}
	clock_t end = clock();
	double runtime = double(end - begin) / CLOCKS_PER_SEC;
	cout << wl;
	clock_t begin2 = clock();
	//call function that finds the words
	findMatches(wl, g);
	clock_t end2 = clock();
	double runtime2 = double(end2 - begin2) / CLOCKS_PER_SEC;
	//print out run times
	cout << "Sort time: " << runtime << endl;
	cout << "Search time: " << runtime2 << endl;
	cout << "Total time: " << runtime + runtime2 << endl;
}