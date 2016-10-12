#include "wordList.h"


wordList::wordList()
{
}


wordList::~wordList()
{
}

void wordList::readWords(const string & fileName)
{
	fstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		cerr << "File not opened.\n";
		throw exception("File not opened\n");
	}
	while (!file.eof())
	{
		string word;
		file >> word;
		words.push_back(word);
	}
	file.close();
}

void wordList::sortInsertion()
{
	for (int i = 1; i < words.size(); i++)
	{
		string currentWord = words.at(i);
		int j = i - 1;
		while (j >= 0 && currentWord < words.at(j))
		{
			words.at(j + 1) = words.at(j);
			words.at(j--) = currentWord;
		}
	}
}

void wordList::sortQuick(int left, int right)
{
	if (right == -1)
	{
		right = words.size() - 1;
	}

	int i = left;
	int j = right;
	string r = words.at((left + right) / 2);

	while (i <= j)
	{
		while (words.at(i) < r)
		{
			i++;
		}
		while (words.at(j) > r)
		{
			j--;
		}

		if (i <= j)
		{
			string swapVar = words.at(i);
			words.at(i) = words.at(j);
			words.at(j) = swapVar;
			i++;
			j--;
		}
	}

	if (left < j)
	{
		sortQuick(left, j);
	}
	if (right >= i)
	{
		sortQuick(i, right);
	}

}

void wordList::merge(int left, int middle, int right)
{
	vector<string> leftVec;
	vector<string> rightVec;
	int leftElements = middle - left + 1;
	int rightElements = right - middle;

	for (int i = 0; i < leftElements; i++)
	{
		leftVec.push_back(words.at(left + i));
	}
	for (int i = 0; i < rightElements; i++)
	{
		rightVec.push_back(words.at(middle + i + 1));
	}

	int i = 0, j = 0, k = left;
	while (i < leftElements && j < rightElements)
	{
		if (leftVec.at(i) <= rightVec.at(j))
		{
			words.at(k++) = leftVec.at(i++);
		}
		else
		{
			words.at(k++) = rightVec.at(j++);
		}
	}

	while (i < leftElements)
	{
		words.at(k++) = leftVec.at(i++);
	}
	while (j < rightElements)
	{
		words.at(k++) = rightVec.at(j++);
	}
}

void wordList::sortMerge(int left, int right)
{
	if (right == -1)
	{
		right = words.size() - 1;
	}

	if (left < right)
	{
		int middle = (left + right) / 2;

		sortMerge(left, middle);
		sortMerge(middle + 1, right);

		merge(left, middle, right);
	}
}

int wordList::hasWord(string word)
{
	int left = 0, middle = (words.size() - 1) / 2, right = words.size() - 1;
	while (left <= right)
	{
		if (words.at(middle) == word) return middle;
		else if (words.at(middle) > word)
		{
			right = middle - 1;
		}
		else
		{
			left = middle + 1;
			
		}
		middle = (left + right) / 2;
	}
	return -1;
}

ostream & operator<<(ostream & os, const wordList & wl)
{
	for (int i = 0; i < wl.words.size(); i++)
	{
		os << wl.words.at(i) << endl;
	}
	return os;
}
