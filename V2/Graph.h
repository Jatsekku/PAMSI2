/*
 * Graph.h
 *
 *  Created on: 29.04.2019
 *      Author: nicdo
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#define INT_MAX 1000
#include "MinHeap.h"


class Graph
{
public:
	int V;
	AdjList* array;
	Graph(int V);
	Graph(FILE* f);
	~Graph();
	bool isEdgeExist(int src, int dest);
	void printGraph_List();
	void fillGraph(float density);
	void addEdge( int src, int dest, int weight);
	void printArr(int dist[], int n);
	void printArrToFile(int dist[], int n);
	void dijkstra(int src);
};

#endif /* GRAPH_H_ */
