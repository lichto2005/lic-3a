//created in Visual Studio using Windows PC
#include "wordList.h"
#include "grid.h"
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

void findMatches(wordList wl, grid g);
void search(int algorithm);

int main()
{
	cout << "Insertion Sort\nType grid file name: ";
	search(0);
	cout << "Quick Sort\nType grid file name: ";
	search(1);
	cout << "Merge Sort\nType grid file name: ";
	search(2);
	return 0;
}

void findMatches(wordList wl, grid g)
{
	cout << "---- FOUND WORDS ----\n";
	for (int i = 0; i < g.rows * g.columns; i++)
	{
		int col = i % g.columns;
		int row = i / g.columns;
		string s_forward;
		string s_up;
		for (int len = 0; len < g.columns; len++)
		{
			s_forward = s_forward + (g.matrix[row][(col + len) % g.columns]);
			if (wl.hasWord(s_forward) != -1 && s_forward.length() >= 5)
			{
				cout << s_forward << endl;
			}
			string s_backward = string(s_forward.rbegin(), s_forward.rend());
			if (wl.hasWord(s_backward) != -1 && s_backward.length() >= 5)
			{
				cout << s_backward << endl;
			}

			s_up = s_up + (g.matrix[(row + len) % g.rows][col]);
			if (wl.hasWord(s_up) != -1 && s_up.length() >= 5)
			{
				cout << s_up << endl;
			}
			string s_down = string(s_up.rbegin(), s_up.rend());
			if (wl.hasWord(s_down) != -1 && s_down.length() >= 5)
			{
				cout << s_down << endl;
			}
		}

		int j = row, k = col;
		string s_up_right;
		do
		{
			s_up_right += g.matrix[j][k];
			if (wl.hasWord(s_up_right) != -1 && s_up_right.length() >= 5)
			{
				cout << s_up_right << endl;
			}
			string s_down_left = string(s_up_right.rbegin(), s_up_right.rend());
			if (wl.hasWord(s_down_left) != -1 && s_down_left.length() >= 5)
			{
				cout << s_down_left << endl;
			}

			if (j == 0 || k == g.rows - 1)
			{
				int temp = j;
				j = k;
				k = temp;
			}
			else
			{
				j--;
				k++;
			}

		} while (j != row && k != col);

		j = row, k = col;
		string s_down_right;
		do
		{
			s_down_right += g.matrix[j][k];
			if (wl.hasWord(s_down_right) != -1 && s_down_right.length() >= 5)
			{
				cout << s_down_right << endl;
			}
			string s_up_left = string(s_down_right.rbegin(), s_down_right.rend());
			if (wl.hasWord(s_up_left) != -1 && s_up_left.length() >= 5)
			{
				cout << s_up_left << endl;
			}

			if (j == g.rows - 1 || k == g.columns - 1)
			{
				int temp = j;
				j = g.columns - 1 - k;
				k = g.rows - 1 - temp;
			}
			else
			{
				j++;
				k++;
			}

		} while (j != row && k != col);
	}
}

void search(int algorithm)
{
	string fileName;
	cin >> fileName;
	grid g;
	g.readGrid(fileName);
	wordList wl;
	wl.readWords("wordlist.txt");
	clock_t begin = clock();
	switch (algorithm)
	{
	case 0:
		wl.sortInsertion();
		break;
	case 1:
		wl.sortQuick(0, -1);
		break;
	case 2:
		wl.sortMerge(0, -1);
		break;
	default:
		cerr << "Invalid algorithm choice. Choose [0,2]\n";
		throw exception("Invalid algorith, choice. Choose [0,2]\n");
	}
	clock_t end = clock();
	double runtime = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Sort time: " << runtime << endl;
	cout << wl;
	clock_t begin2 = clock();
	findMatches(wl, g);
	clock_t end2 = clock();
	double runtime2 = double(end2 - begin2) / CLOCKS_PER_SEC;
	cout << "Search time: " << runtime2 << endl;
	cout << "Total time: " << runtime + runtime2 << endl;
}