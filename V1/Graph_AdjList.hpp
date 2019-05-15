#ifndef GRAPH_ADJLIST_HPP_
#define GRAPH_ADJLIST_HPP_
#include <iostream>
#include "list\dlist.hpp"
#include "pair.hpp"


template <typename T, typename W>
class GraphAdjList{
  public:
	struct Edge;
	struct Vertex;

	dlinklist<Edge*> edge_list;
	dlinklist<Vertex*> vertex_list;
	int vertices_amount;

	//Access method
	Pair<Vertex*, Vertex*>endVertices(Edge *E)
	{
		Pair<Vertex*, Vertex*> pair_tmp;
		pair_tmp.first = E->start;
		pair_tmp.second = E->end;

		return pair_tmp;
	}

	Vertex* opposite(Vertex* V, Edge* E)
	{
		if(E->start == V)
			return E->end;
		return E->start;
	}

	bool areAdjacent(Vertex* V1, Vertex* V2)
	{
		if((V1->inclist.begin() != nullptr) && (V2->inclist.begin() != nullptr))
		{
			for(auto i = V1->inclist.begin(); i != V1->inclist.end(); i++)
				for(auto j = V2->inclist.begin(); j != V2->inclist.end(); j++)
					if(*i==*j)
						return true;
		}
		return false;
	}

	void replace(Vertex* V, W X) { V->data = X;}

	void replace(Edge* E, W X) { E->weight = X;}

	//Update methods
	Vertex* insertVertex(W O)
	{
		Vertex* vertex_tmp = new Vertex;
		vertex_tmp->data = O;
		vertex_list.push_front(vertex_tmp);
		return vertex_tmp;
	}

	Edge* insertEdge(Vertex* V_start, Vertex* V_end, W O)
	{
		Edge* edge_tmp = new Edge;
		edge_tmp->start = V_start;		//Wierzchołek początkowy
		edge_tmp->end = V_end;			//Wierzchołek końcowy
		edge_tmp->weight = O;

		V_start->inclist.push_front(edge_tmp);
		V_end->inclist.push_front(edge_tmp);

		edge_tmp->inclist_start = V_start->inclist.front();
		edge_tmp->inclist_end = V_end->inclist.front();

		edge_list.push_front(edge_tmp);
		return edge_tmp;
	}

	void removeVertex(Vertex *V)
	{
		Edge* edge_tmp;
		for(auto j = vertex_list.begin(); j != vertex_list.end(); j++)
		{
			if(*j == V)
			{
				for(auto i = V->inclist.begin(); i != V->inclist.end(); i++)
				{
					edge_tmp = *i;
					removeEdge(edge_tmp);
				}

				vertex_list.erase(j);
				delete V;
				break;
			}
		}
	}

	void removeEdge(Edge* E)
	{
		auto i = E->start->inclist.begin();
		auto j = E->end->inclist.begin();

		for(; i != E->start->inclist.end(); i++)
		{
			if(*i == E->inclist_start)
			{
				//cout << "ok1" <<endl;
				//E->start->inclist.erase(i);
				//cout << "ok2" <<endl;
				break;
			}
		}

		for(; j != E->end->inclist.end(); j++)
		{
			if(*j == E->inclist_end)
			{
				//cout << "ok3" << endl;
				//E->end->inclist.erase(j);
				//cout << "ok4" <<endl;
				break;
			}
		}


		for(auto k = edge_list.begin(); k != edge_list.end(); k++)
		{

			if(*k == E)
			{
				E->start->inclist.erase(i);
				E->end->inclist.erase(j);
				edge_list.erase(k);
				delete E;
				break;
			}
		}


	}

	//Iterator methods
	dlinklist<Edge*> incidentEdges(Vertex* V) {return V->inclist;}

	dlinklist<Vertex*> vertices(void) {return vertex_list;}

	dlinklist<Edge*> edges(void) {return edge_list;}

	//Additional methods
	void displayVertices(void)
	{
		std::cout << "displayVertices():" << std::endl;
		Vertex* vertex_tmp;
		for(auto i = vertex_list.begin(); i != vertex_list.end(); i++)
		{
			vertex_tmp = *i;
			std::cout << "Address: " << vertex_tmp << " Data: " << vertex_tmp->data << std::endl;
		}
	}

	void displayEdges(void)
	{
		cout << "displayEdges():" << std::endl;
		Edge* edge_tmp;
		for(auto i = edge_list.begin(); i != edge_list.end(); i++)
		{
			edge_tmp = *i;
			std::cout << "Address: " << edge_tmp << " Weight: " << edge_tmp->weight << std::endl;
		}
	}

	GraphAdjList(int V_amount, float G_density)
	{
		int E_amount_max = (V_amount*V_amount - V_amount);
		int E_amount = G_density * E_amount_max;
		Vertex* V_curr[V_amount];

		for(int i = 0; i < V_amount; i++)
			V_curr[i] = insertVertex(i);

		int added_edges = 0;
		for(int a = 0; a < E_amount/V_amount + 1; a++)
			for(int b = 0; b < V_amount; b++)
				if( !((a == b) || added_edges > E_amount))
				{
					insertEdge(V_curr[a], V_curr[b], a+b);
					added_edges++;
				}
	}


	struct Vertex
	{
		W data;
		dlinklist<Edge*> inclist;
	};

	struct Edge
	{
		W weight;
		struct Vertex* start;
		struct Vertex* end;
		Edge* inclist_start;
		Edge* inclist_end;
	};

};
#endif
