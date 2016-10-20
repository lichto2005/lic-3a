#include "wordList.h"
#include "heap.h"

wordList::wordList()
{
}


wordList::~wordList()
{
}

//readwords takes a filename and populates the words vector
void wordList::readWords(const string & fileName)
{
	//open file
	fstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		cerr << "File not opened.\n";
		throw exception("File not opened\n");
	}
	while (!file.eof())
	{
		//read in words
		string word;
		file >> word;
		//add to array
		words.push_back(word);
	}
	file.close();
}

//insertion sort
void wordList::sortInsertion()
{
	//declare first element sorted
	//starting with first unsorted element and for all elements
	for (int i = 1; i < words.size(); i++)
	{
		//store the word to be sorted
		string currentWord = words.at(i);
		int j = i - 1;
		//while current word is not in the proper lexographic place
		while (j >= 0 && currentWord < words.at(j))
		{
			// shift the word over
			words.at(j + 1) = words.at(j);
			words.at(j--) = currentWord;
		}
	}
}

//quick sort
void wordList::sortQuick(int left, int right)
{
	// if given sentinel value -1, right is words.size
	// this is because words is a private member of worldlist and main function cannot access length of the list
	if (right == -1)
	{
		right = words.size() - 1;
	}

	//set indices and pick the pivot value
	int i = left;
	int j = right;
	string r = words.at((left + right) / 2);

	//while i is on the left side, and j is on the right side
	while (i <= j)
	{
		//find a word that needs to be swapped from L side to R side
		while (words.at(i) < r)
		{
			i++;
		}
		//find a word that needs to be swapped from R side to L side
		while (words.at(j) > r)
		{
			j--;
		}

		//if indices did not mess up while finding
		if (i <= j)
		{
			//swap the two words in need of swapping
			string swapVar = words.at(i);
			words.at(i) = words.at(j);
			words.at(j) = swapVar;
			//advance indices
			i++;
			j--;
		}
	}

	//if index still in range
	if (left < j)
	{
		//recursive call quicksort
		sortQuick(left, j);
	}
	//if index still in range
	if (right >= i)
	{
		//recursive call quicksort
		sortQuick(i, right);
	}

}

//merge function for use in mergesort
//assumes sorted vectors
void wordList::merge(int left, int middle, int right)
{
	//declare temp vectors and their sizes
	vector<string> leftVec;
	vector<string> rightVec;
	int leftElements = middle - left + 1;
	int rightElements = right - middle;

	//copy left side from main vector
	for (int i = 0; i < leftElements; i++)
	{
		leftVec.push_back(words.at(left + i));
	}
	//copy right side from main vector
	for (int i = 0; i < rightElements; i++)
	{
		rightVec.push_back(words.at(middle + i + 1));
	}

	//while there are elements in both vectors
	int i = 0, j = 0, k = left;
	while (i < leftElements && j < rightElements)
	{
		//take the lowest element at the front of either array and add back to words in proper sorted place
		if (leftVec.at(i) <= rightVec.at(j))
		{
			words.at(k++) = leftVec.at(i++);
		}
		else
		{
			words.at(k++) = rightVec.at(j++);
		}
	}

	//once one vector is empty, copy remaining items back into words vector
	while (i < leftElements)
	{
		words.at(k++) = leftVec.at(i++);
	}
	while (j < rightElements)
	{
		words.at(k++) = rightVec.at(j++);
	}
}

//merge sort
void wordList::sortMerge(int left, int right)
{
	//sentinel value retrieves private member words.size
	if (right == -1)
	{
		right = words.size() - 1;
	}

	//if index is still in bounds
	if (left < right)
	{
		//determine the middle
		int middle = (left + right) / 2;

		//call recursive mergesort on left and right sdies
		sortMerge(left, middle);
		sortMerge(middle + 1, right);

		//merge the result back together
		merge(left, middle, right);
	}
}

//binary search method returns index of word in wordlist
bool wordList::inList(string word)
{
	//determine the left right and middle of the initial list
	int left = 0, middle = (words.size() - 1) / 2, right = words.size() - 1;
	//while still have an array to search
	while (left <= right)
	{
		//if the word is in the middle, return index of word
		if (words.at(middle) == word) return true;
		//if word is in left portion
		else if (words.at(middle) > word)
		{
			//adjust index so right is the middle
			right = middle - 1;
		}
		//else word is in right portion
		else
		{
			//adjust index so left is one past the middle
			left = middle + 1;
			
		}
		// recompute the middle
		middle = (left + right) / 2;
	}
	//if not found, return -1 to denote not in list
	return false;
}

void wordList::sortHeap()
{
	heap<string> myHeap;
	myHeap.initializeMaxHeap(words);
	myHeap.heapSort();
	for (int i = 0; i < words.size(); i++)
	{
		words.at(i) = myHeap.getItem(i);
	}
}

//overloaded print operator prints the entire list
ostream & operator<<(ostream & os, const wordList & wl)
{
	for (int i = 0; i < wl.words.size(); i++)
	{
		os << wl.words.at(i) << endl;
	}
	return os;
}
