#pragma once
#include <algorithm>

template<class T>
class hashTable
{
private:
	int length;
	vector<vector<T>> ht;
	int hash(T item);
public:
	hashTable<T>(int length);
	void addItem(T item);
	void deleteItem(T item);
	bool inList(T key);
};

template<class T>
hashTable<T>::hashTable(int l)
{
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
	int index = hash(item);
	ht.at(index).push_back(item);
}

template<class T>
void hashTable<T>::deleteItem(T item)
{
	int index = hash(item);
	if (std::find(ht.at(index).begin(), ht.at(index).end(), item) != ht.at(index).end())
	{
		ht.at(index).remove(std::find(ht.at(index).begin(), ht.at(index).end(), item))
	}
}

template<class T>
bool hashTable<T>::inList(T key)
{
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

template<class T>
int hashTable<T>::hash(T item)
{
	int sum = 0;
	for (int i = 0; i < item.length(); i++)
	{
		sum += item.at(i);
	}

	return sum % length;
}
