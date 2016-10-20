#pragma once

template <class T>
class heap
{
private:
	vector<T> h;
	int heapsize;

public:
	heap<T>();
	heap<T>(vector<T> h);

	int parent(int child);
	int left(int parent);
	int right(int parent);
	T getItem(int n);
	vector<T> getHeap();

	void initializeMaxHeap();
	void maxHeapify(int i);
	void buildMaxHeap();

	void initializeMinHeap();
	void minHeapify(int i);
	void buildMinHeap();

	void heapSort();
};

template<class T>
heap<T>::heap()
{

}

template<class T>
heap<T>::heap(vector<T> data)
{
	h = data;
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
vector<T> heap<T>::getHeap()
{
	return h;
}

template<class T>
void heap<T>::initializeMaxHeap()
{
	heapsize = h.size();
}

template<class T>
void heap<T>::maxHeapify(int i)
{
	int l = left(i);
	int r = right(i);
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

	if (largest != i)
	{
		T temp = h.at(i);
		h.at(i) = h.at(largest);
		h.at(largest) = temp;
		maxHeapify(largest);
	}
}

template<class T>
void heap<T>::buildMaxHeap()
{
	initializeMaxHeap();
	for (int i = h.size() / 2 - 1; i >= 0; i--)
	{
		maxHeapify(i);
	}
}

template<class T>
void heap<T>::heapSort()
{
	buildMaxHeap();
	for (int i = h.size() - 1; i >= 0; i--)
	{
		T temp = h.at(i);
		h.at(i) = h.at(0);
		h.at(0) = temp;

		maxHeapify(0);
		heapsize--;
	}
}

template<class T>
void heap<T>::initializeMinHeap()
{
	heapsize = h.size();
}

template<class T>
void heap<T>::minHeapify(int i)
{
	int l = left(i);
	int r = right(i);
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
	initializeMinHeap();
	for (int i = h.size() / 2 - 1; i >= 0; i--)
	{
		minHeapify(i);
	}
}