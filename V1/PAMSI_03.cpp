#include <iostream>
#include "Graph_AdjList.hpp"
#include "Graph_AdjMatrix.hpp"

#include "pair.hpp"
//#include<bits/stdc++.h>





FILE* file_open(const char *adress, const char *operation)
{
	FILE* file;
	file = fopen(adress, operation);
	if (file == 0)
	{
		cout << "File isn't open." << endl;
		return 0;
	}
	return file;
}

int main(int argc,char **argv)
{

	GraphAdjMx<int, int> graf;
	auto v0 = graf.insertVertex(1);
	auto v1 = graf.insertVertex(2);
	auto v2 = graf.insertVertex(3);
	auto v3 = graf.insertVertex(4);


	graf.insertEdge(v0, v1, 3);
	graf.insertEdge(v1, v2, 1);
	graf.insertEdge(v2,v3, 2);
	graf.insertEdge(v3, v0, 4);





	graf.V_tmp = v0;
	//GraphAdjMx<int, int> graf( file_open(argv[1], "a+"));
	//GraphAdjMx<int, int> graf(10, 0.25);
	graf.displayVertices();
	graf.displayEdges();
	graf.dijkstra();


}
