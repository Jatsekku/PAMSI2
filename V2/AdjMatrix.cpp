#include "AdjMatrix.h"
#define INT_MAX 2000000

AdjMatrix::AdjMatrix(int n)
{
	this->n = n;
	visited = new bool[n];
	adj = new int*[n];
	for(int i = 0; i < n; i++)
	{
		adj[i] = new int [n];
		for(int j = 0; j < n; j++)
		{
			adj[i][j] = 0;
		}
	}
}

AdjMatrix::~AdjMatrix()
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			delete adj[j];
		}
		delete adj[i];
	}
	delete adj;
}

void AdjMatrix::addEdge(int src, int dest, int cost)
{
	adj[src][dest] = cost;
}

int AdjMatrix::minDist(int dist[], bool sptSet[])
{
	int min = INT_MAX;
	int min_idx;
	for (int i = 0; i < n; i++)
	{
		if(sptSet[i] == false && dist[i] <= min)
		{
			min = dist[i];
			min_idx = i;
		}
	}
	return min_idx;
}

void AdjMatrix::printSolution(int dist[], int n)
{
	for(int i = 0; i < n; i++)
	{
		std::cout << "   " << i << "          " << dist[i] << std::endl;
	}
}

void AdjMatrix::dijkstra(int src)
{
	int dist[n];
	bool sptSet[n];
	for(int i = 0; i < n; i++)
	{
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}

	dist[src] = 0;

	for(int i = 0; i < n-1; i++)
	{
		int u = minDist(dist, sptSet);
		sptSet[u] = true;


		for(int j = 0; j < n; j++)
		{
			if(!sptSet[j] && this->adj[u][j] && dist[u] != INT_MAX && dist[u] + this->adj[u][j] < dist[j])
			{
				dist[j] = dist[u] + adj[u][j];
			}
		}
	}
//	this->printSolution(dist, n);
}

void AdjMatrix::fill(float denisty)
{
	int n = this->n;
	int edges = 0.5*(n*n - n)*denisty;
	int a = 0;
	for(int i = 0; i < edges; i++)
	{
		int b = std::rand()%n;
		while(a==b || adj[a][b] != 0) b = std::rand()%n;
		int c = std::rand()%5+1;
		addEdge(a, b, c);
		if(a < n-1) a++;
		else a = 0;
	}


}
