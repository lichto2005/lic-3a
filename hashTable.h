#pragma once

template<class T>
class hashTable
{
private:
	int num_elements = 0;
	vector<vector<T>> ht;
public:
	hashTable<T>();

	void addItem(T item);
	void deleteItem(T item);
	void inList();
	int hash(T item);
};

template<class T>
hashTable<T>::hashTable()
{
}

template<class T>
void hashTable<T>::addItem(T item)
{

}

template<class T>
void hashTable<T>::deleteItem(T item)
{
}

template<class T>
void hashTable<T>::inList()
{
}

template<class T>
int hashTable<T>::hash(T item)
{
}
