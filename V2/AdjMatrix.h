#ifndef ADJMATRIX_H_
#define ADJMATRIX_H_
#include <iostream>


class AdjMatrix
{
public:
	int n;
	int **adj;
	bool *visited;

	AdjMatrix(int n);
	~AdjMatrix();
	void addEdge(int src, int dest, int cost);
	int minDist(int dist[], bool sptSet[]);
	void printSolution(int dist[], int n);
	void fill(float denisty);
	void dijkstra(int src);
};

#endif /* ADJMATRIX_H_ */
