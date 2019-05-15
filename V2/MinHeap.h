#ifndef MINHEAP_H_
#define MINHEAP_H_
#include "MinHeapN.h"


class MinHeap
{
public:
	int size;
	int capacity;
	int *pos;
	MinHeapNode *array;
	MinHeap (int capacity);

	void minHeapify(int idx);
	void decreaseKey(int v, int dist);
	bool isInMinHeap(int v);
	bool isEmpty();
	MinHeapNode extractMin();

};
#endif /* MINHEAP_H_ */
