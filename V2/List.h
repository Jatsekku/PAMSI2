#ifndef LIST_H_
#define LIST_H_
#include <iostream>


struct AdjListNode
{
	int dest;
	int weight;
	AdjListNode* next;

};



class AdjList
{
public:
	struct AdjListNode *head; // pointer to head node of list
	AdjList();
	void push(int dest, int weight);
//	AdjListNode* front()
//	void isEdgeExist(int src, int dest);



};
#endif /* LIST_H_ */
