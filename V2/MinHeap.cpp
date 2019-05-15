#include "MinHeap.h"


MinHeap::MinHeap(int capacity)
{
	this->pos = new int[capacity];
	this->size = 0;
	this->capacity = capacity;
	this->array = new MinHeapNode[capacity];
}

void MinHeap::minHeapify(int idx)
{
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < this->size &&
		this->array[left].dist < this->array[smallest].dist )
	smallest = left;

	if (right < this->size &&
		this->array[right].dist < this->array[smallest].dist )
	smallest = right;

	if (smallest != idx)
	{

		MinHeapNode smallestNode = this->array[smallest];
		MinHeapNode idxNode = this->array[idx];


		this->pos[smallestNode.v] = idx;
		this->pos[idxNode.v] = smallest;


		this->array[smallest].swapMinHeapNode(&this->array[idx]);

		minHeapify(smallest);
	}
}

void MinHeap::decreaseKey(int v, int dist)
{

	int i = this->pos[v];


	this->array[i].dist = dist;


	while (i && this->array[i].dist < this->array[(i - 1) / 2].dist)
	{

		this->pos[this->array[i].v] = (i-1)/2;
		this->pos[this->array[(i-1)/2].v] = i;
		this->array[i].swapMinHeapNode(&this->array[(i - 1) / 2]);


		i = (i - 1) / 2;
	}
}

bool MinHeap::isInMinHeap(int v)
	{
	if (this->pos[v] < this->size)
		return true;
	return false;
	}

bool MinHeap::isEmpty()
{
	return this->size == 0;
}

MinHeapNode MinHeap::extractMin()
	{
		if (this->isEmpty())
			std::cout << "minHeap empty" << std::endl;


		MinHeapNode root = this->array[0];


		MinHeapNode lastNode = this->array[this->size - 1];
		this->array[0] = lastNode;


		this->pos[root.v] = this->size-1;
		this->pos[lastNode.v] = 0;


		--this->size;
		this->minHeapify(0);

		return root;
	}







