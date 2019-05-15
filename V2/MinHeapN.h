#ifndef MINHEAPN_H_
#define MINHEAPN_H_
#include "List.h"

class MinHeapNode
{
public:
	int v;
	int dist;
	MinHeapNode();
	MinHeapNode(int v, int dist);

	void swapMinHeapNode(MinHeapNode *b);
};

#endif /* MINHEAPN_H_ */
