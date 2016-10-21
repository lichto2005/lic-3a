#pragma once

// heap template class to store and sort a heap data structure implemented as a vector of type T
template <class T>
class heap
{
private:
	// vector to store heap and size of heap
	vector<T> h;
	int heapsize;

public:
	heap<T>();

	int parent(int child); //returns the parent index of a child
	int left(int parent); //returns the left child index of a parent
	int right(int parent); //returns the right child index of a parent
	T getItem(int n); //returns an item at index n

	void initializeMaxHeap(vector<T> list); //copy words into heap
	void maxHeapify(int i); //establish max heap property of one sub-branch
	void buildMaxHeap(); //establish max heap property of array

	void initializeMinHeap(vector<T> list); //copy words into heap
	void minHeapify(int i); //establish min heap property of one sub-branch
	void buildMinHeap(); //establish min heap property of array

	void heapSort(); //maxheap sort
};

template<class T>
heap<T>::heap()
{
}

template<class T>
int heap<T>::parent(int child)
{
	return child % 2 == 0 ? child / 2 - 1 : child / 2;
}

template<class T>
int heap<T>::left(int parent)
{
	return 2*parent + 1;
}

template<class T>
int heap<T>::right(int parent)
{
	return 2*parent + 2;
}

template<class T>
T heap<T>::getItem(int n)
{
	return h.at(n);
}

template<class T>
void heap<T>::initializeMaxHeap(vector<T> list)
{
	h = list;
	buildMaxHeap();
}

template<class T>
void heap<T>::maxHeapify(int i)
{
	// get index of left and right childen of element i
	int l = left(i);
	int r = right(i);

	// determine the largest of the 3 elements
	int largest;
	if (l < heapsize && h.at(l) > h.at(i))
	{
		largest = l;
	}
	else
	{
		largest = i;
	}

	if (r < heapsize && h.at(r) > h.at(largest))
	{
		largest = r;
	}

	// if largest is not already parent, swap to make it parent
	if (largest != i)
	{
		T temp = h.at(i);
		h.at(i) = h.at(largest);
		h.at(largest) = temp;
		// propagate this change through the rest of the tree
		maxHeapify(largest);
	}
}

template<class T>
void heap<T>::buildMaxHeap()
{
	// set heapsize to size of array
	heapsize = h.size();
	// heapify entire array
	for (int i = h.size() / 2 - 1; i >= 0; i--)
	{
		maxHeapify(i);
	}
}

template<class T>
void heap<T>::heapSort()
{
	//heapify entire array
	buildMaxHeap();
	//loop over entire array
	for (int i = h.size() - 1; i >= 0; i--)
	{
		//swap 0 and i
		T temp = h.at(i);
		h.at(i) = h.at(0);
		h.at(0) = temp;

		//heapify array
		maxHeapify(0);
		//shrink unsorted portion (heap) by one
		heapsize--;
	}
}

template<class T>
void heap<T>::initializeMinHeap(vector<T> list)
{
	h = list;
	buildMinHeap();
}

template<class T>
void heap<T>::minHeapify(int i)
{
	//get child indices
	int l = left(i);
	int r = right(i);

	//choose lowest to be parent
	int largest;
	if (l < heapsize && h.at(l) < h.at(i))
	{
		largest = l;
	}
	else
	{
		largest = i;
	}

	if (r < heapsize && h.at(r) < h.at(largest))
	{
		largest = r;
	}

	//swap and fix rest of tree
	if (largest != i)
	{
		T temp = h.at(i);
		h.at(i) = h.at(largest);
		h.at(largest) = temp;
		minHeapify(largest);
	}
}

template<class T>
void heap<T>::buildMinHeap()
{
	//heapify entire array
	heapsize = h.size();
	for (int i = h.size() / 2 - 1; i >= 0; i--)
	{
		minHeapify(i);
	}
}