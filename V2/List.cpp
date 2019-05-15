#include "List.h"

struct AdjListNode* newAdjListNode(int dest, int weight)
{
	AdjListNode* newNode = new AdjListNode;
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}

AdjList::AdjList()
{
	this->head = 0;
}

void AdjList::push(int dest, int weight)
{
	AdjListNode* newNode = new AdjListNode;
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = this->head;
	this->head = newNode;
}


