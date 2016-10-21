#pragma once
#include <algorithm>

template<class T>
class hashTable
{
private:
	int length; //length of table
	vector<vector<T>> ht; //bins
	int hash(T item); //private function that determines the bin for a given item
public:
	hashTable<T>(int length); //make hashtable with length length
	void addItem(T item); //add an item to the table
	void deleteItem(T item); //delete an item from the table
	bool inList(T key); //check if a key is in the table
};

template<class T>
hashTable<T>::hashTable(int l)
{
	// init table with length l
	length = l;
	for (int i = 0; i < length; i++)
	{
		vector<T> bin;
		ht.push_back(bin);
	}
}

template<class T>
void hashTable<T>::addItem(T item)
{
	//get the hash of the item and place it in the correct pin
	int index = hash(item);
	ht.at(index).push_back(item);
}

template<class T>
void hashTable<T>::deleteItem(T item)
{
	// find the hash of the item, check if it is in the bin, if so, remove it
	int index = hash(item);
	if (std::find(ht.at(index).begin(), ht.at(index).end(), item) != ht.at(index).end())
	{
		ht.at(index).remove(std::find(ht.at(index).begin(), ht.at(index).end(), item))
	}
}

template<class T>
bool hashTable<T>::inList(T key)
{
	// find the hash of the item, check if it is in the bin, if so, return true
	int index = hash(key);
	if (std::find(ht.at(index).begin(), ht.at(index).end(), key) != ht.at(index).end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

// hash function assumes that hashTable.length was chosen to be a prime number not near any power of 2
// so as to allow even distribution between bins
// hash function works irrespective of the rarity of the individual values of the item
template<class T>
int hashTable<T>::hash(T item)
{
	// sum the value of the item
	int sum = 0;
	for (int i = 0; i < item.length(); i++)
	{
		sum += 23 * item.at(i);
	}
	
	// make the sum a unique value not dependent on the distribution of letters
	// mod it so it fits in the table
	return (sum * item.length()) % length;
}
