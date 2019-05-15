#include "MinHeapN.h"


MinHeapNode::MinHeapNode()
{
	this->v = 0;
	this->dist = 0;
}

MinHeapNode::MinHeapNode(int v, int dist)
{
	this->v = v;
	this->dist = dist;
}

void MinHeapNode::swapMinHeapNode(MinHeapNode *b)
{
	int tmp_dist = this->dist;
	int tmp_v = this->v;
	this->dist = b->dist;
	this->v = b->v;
	b->dist = tmp_dist;
	b->v = tmp_v;
}



