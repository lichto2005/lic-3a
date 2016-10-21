//created in Visual Studio using Windows PC
#include "wordList.h"
#include "grid.h"
#include "hashTable.h"
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

//declare global functions
//void findMatches(wordList wl, grid g);
void search(int algorithm);

//program start
int main()
{
	cout << "Hash Table\nType grid file name: ";
	search(4);
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

// template function takes in a list of words stored in data type T
// assumes T has the function bool T::inList(item)
template<class T>
void findMatches(T wl, grid g)
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
			if (wl.inList(s_forward) == true && s_forward.length() >= 5)
			{
				cout << s_forward << endl;
			}
			// check from right to left by reversing string
			string s_backward = string(s_forward.rbegin(), s_forward.rend());
			// see if it matches a word
			if (wl.inList(s_backward) == true && s_backward.length() >= 5)
			{
				cout << s_backward << endl;
			}

			// concat a string with the next letter up
			s_up = s_up + (g.matrix[(row + len) % g.rows][col]);
			// see if it matches a word
			if (wl.inList(s_up) == true && s_up.length() >= 5)
			{
				cout << s_up << endl;
			}
			// check the down direction by reversing string
			string s_down = string(s_up.rbegin(), s_up.rend());
			// see if it matches a word
			if (wl.inList(s_down) == true && s_down.length() >= 5)
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
			if (wl.inList(s_up_right) == true && s_up_right.length() >= 5)
			{
				cout << s_up_right << endl;
			}
			// reverse string to check down-left
			string s_down_left = string(s_up_right.rbegin(), s_up_right.rend());
			// check if word
			if (wl.inList(s_down_left) == true && s_down_left.length() >= 5)
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
			if (wl.inList(s_down_right) == true && s_down_right.length() >= 5)
			{
				cout << s_down_right << endl;
			}
			//reverse string to check up-left
			string s_up_left = string(s_down_right.rbegin(), s_down_right.rend());
			//check if word
			if (wl.inList(s_up_left) == true && s_up_left.length() >= 5)
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
	hashTable<string> myHash(29959); // prime not near a pow(2), and made such that we expect avg 3 collisions
	clock_t begin = clock();
	// sort based on parameter
	switch (algorithm)
	{
	case 4:
		//if using hash, add all the words from wl into hashtable
		for (int i = 0; i < wl.words.size(); i++)
		{
			myHash.addItem(wl.words.at(i));
		}
		break;
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
	// print sorted words if using a sort function
	if (algorithm != 4) cout << wl;
	clock_t begin2 = clock();
	//call function that finds the words
	if (algorithm != 4) findMatches(wl, g);
	else findMatches(myHash, g);
	clock_t end2 = clock();
	double runtime2 = double(end2 - begin2) / CLOCKS_PER_SEC;
	//print out run times
	cout << "Sort time: " << runtime << endl;
	cout << "Search time: " << runtime2 << endl;
	cout << "Total time: " << runtime + runtime2 << endl;
}