
#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

Graph::Graph(int V)
{
	this->V = V;
	this->array = new AdjList[V];
}

Graph::~Graph()
{
	for(int i = 0; i < this->V; i++)
	{
		delete array[i].head;
	}
	delete array;

}

bool Graph::isEdgeExist(int src, int dest)
{
	AdjListNode* node_tmp = this->array[src].head;
	while(node_tmp != nullptr)
	{
		if(node_tmp->dest == dest)
			return true;
		node_tmp = node_tmp->next;
	}
	return false;
}

void Graph::fillGraph(float denisty)
{
	int V = this->V;
	int edges = 0.5*(V*V - V)*denisty;

	int a = 0;

	for(int i = 0; i < edges; i++)
	{

		int b = std::rand()%V;

		while(a == b || this->isEdgeExist(a, b) == true) b = std::rand()%V;

		int c = std::rand()%5+1;
		this->addEdge(a, b, c);

		if (a < V-1)a++;
		else a = 0;
	}
}


void Graph:: addEdge( int src, int dest, int weight)
{
	this->array[src].push(dest, weight);
}

void Graph::printArr(int dist[], int n)
{
	printf("Vertex Distance from Source\n");
	for (int i = 0; i < n; ++i)
		if (dist[i] < INT_MAX)
		std::cout << "   " << i << "            " << dist[i] << std::endl;
		else std::cout << "   " << i << "            " << "x" << std::endl;
}

void Graph::printArrToFile(int dist[], int n)
{
	FILE* file = fopen("F:\\Programowanie\\Eclipse_Workspace\\PAMSI_05\\g.txt", "a+");
	for (int i = 0; i < n; ++i)
	{
		if(dist[i] < INT_MAX)
			fprintf(file, "    %d  %d \n", i, dist[i]);
		else fprintf(file, "    %d  x \n", i);
	}
}

void Graph::dijkstra(int src)
{
	int V = this->V;
	int dist[V];


	MinHeap minHeap(V);


	for (int v = 0; v < V; ++v)
	{
		dist[v] = INT_MAX;
		minHeap.array[v] = MinHeapNode(v, dist[v]);
		minHeap.pos[v] = v;
	}

	minHeap.array[src] = MinHeapNode(src, dist[src]);
	minHeap.pos[src] = src;
	dist[src] = 0;
	minHeap.decreaseKey(src, dist[src]);


	minHeap.size = V;


	while (!minHeap.isEmpty())
	{

		MinHeapNode minHeapNode = minHeap.extractMin();
		int u = minHeapNode.v;

		struct AdjListNode* pCrawl = this->array[u].head;
		while (pCrawl != NULL)
		{
			int v = pCrawl->dest;

			if (minHeap.isInMinHeap(v) && dist[u] != INT_MAX &&
										pCrawl->weight + dist[u] < dist[v])
			{
				dist[v] = dist[u] + pCrawl->weight;

				minHeap.decreaseKey(v, dist[v]);
			}
			pCrawl = pCrawl->next;
		}
	}


	//this->printArr(dist, V);
}
