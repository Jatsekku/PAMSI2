#ifndef GRAPH_ADJMATRIX_HPP_
#define GRAPH_ADJMATRIX_HPP_
#include "list/dlist.hpp"
#include "matrix/matrix.hpp"
#include "priority_queue/priority_queue.hpp"
#include "pair.hpp"



template <typename T, typename W>
class GraphAdjMx{
  public:
	struct Edge;
	struct Vertex;

	Vertex* V_tmp;
	dlinklist<Edge*> edge_list;
	dlinklist<Vertex*> vertex_list;
	Matrix<Edge*> adjency_matrix;
	int vertices_amount;

	//Access methods
	Pair<Vertex*, Vertex*>endVertices(Edge* E)
	{
		Pair<Vertex*, Vertex*> pair_tmp;
		pair_tmp.first = E->vertex_start;
		pair_tmp.second = E->vertex_end;

		return pair_tmp;
	}

	Vertex* opposite(Vertex * V, Edge * E)
	{
		if(E->vertex_start == V) return E->vertex_end;
		return E->vertex_start;
	}

    bool areAdjacent(Vertex *V1,Vertex *V2)
    {
    	if(adjency_matrix(V1->idx, V2->idx) != nullptr)
    		return true;
    	return false;
    }

	void replace(Vertex* V, W X) { V->data = X;}

	void replace(Edge* E, W X) { E->weight = X;}

	//Update methods
	Vertex* insertVertex(W O)
	{
		Vertex* vertex_tmp = new Vertex;
		vertex_tmp->data = O;
		vertex_tmp->idx = vertices_amount;
		vertices_amount++;

		if(vertices_amount > adjency_matrix.size())
			adjency_matrix.resize(adjency_matrix.size()*2);

		vertex_list.push_front(vertex_tmp);
		return vertex_tmp;
	}

	Edge* insertEdge(Vertex* V_start, Vertex* V_end, W O)
	{
		Edge* edge_tmp = new Edge;

		edge_tmp->weight = O;
		edge_tmp->vertex_start = V_start;
		edge_tmp->vertex_end = V_end;

		edge_list.push_front(edge_tmp);
		adjency_matrix(V_start->idx, V_end->idx) = edge_tmp;
		adjency_matrix(V_end->idx, V_start->idx) = edge_tmp;
		return edge_tmp;
	}

	void removeVertex(Vertex* V){

		for(int x=0;x<vertices_amount;x++){
			if(adjency_matrix(V->idx,x) !=nullptr){
               //removeEdge(adjency_matrix(V->idx,x));
				adjency_matrix(V->idx,x)=nullptr;}
		           }
		for(int x=0;x<vertices_amount;x++){
			if(adjency_matrix(x,V->idx) !=nullptr){
			   // removeEdge(adjency_matrix(x,V->idx));
				adjency_matrix(x,V->idx)=nullptr;}
		            }

		for(auto k = vertex_list.begin(); k != vertex_list.end(); k++)
			{
				if(*k == V)
				{
					vertex_list.erase(k);
					delete V;
					break;
				}
			}
	}

	void removeEdge(Edge* E){
		for(int x=0;x<vertices_amount;x++)
			for(int y=0;y<vertices_amount ;y++)
			{
				if(adjency_matrix(x,y)==E)
				{
					adjency_matrix(x,y)=nullptr;
				}
			}
		for(auto k = edge_list.begin(); k != edge_list.end(); k++)
		{
			if(*k == E)
			{
				edge_list.erase(k);
				delete E;
				break;
			}
		}
	}

	//Iterator methods
	Edge** incidentEdges(Vertex* V)
	{
		Edge** data_tmp = adjency_matrix.data();
		data_tmp += V->idx * vertices_amount;
		return data_tmp;
	}

	dlinklist<Vertex*> vertices(void) {return vertex_list;}

	dlinklist<Edge*> edges(void) {return edge_list;}

	//Additional methods
	void displayIncidentEdges(Vertex* V)
	{
		std::cout << "displayIncidentEdges" << std::endl;
		Edge** edges_tmp = incidentEdges(V);
		for(int i = 0; i < vertices_amount; i++)
			std::cout << "Address: " << edges_tmp[i] << "Data: " << edges_tmp[i]->weight << std::endl;
	}

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

	GraphAdjMx(void)
  	{
		vertices_amount = 0;
  	};

	GraphAdjMx(int V_amount, float G_density)
	{
		vertices_amount =0;

		int E_amount_max = (V_amount*V_amount - V_amount);
		int E_amount = G_density * E_amount_max;
		Vertex* V_curr[V_amount];

		for(int i = 0; i < V_amount; i++)
			V_curr[i] = insertVertex(i);
		V_tmp = V_curr[0];

		int added_edges = 0;
		int val = 0;
		for(int a = 0; a < E_amount/V_amount + 1; a++)
			for(int b = 0; b < V_amount; b++)
				if( !((a == b) || added_edges > E_amount))
				{
					insertEdge(V_curr[a], V_curr[b], val++);
					added_edges++;
				}
	}

	void AdjencyMatrix_display(void) {adjency_matrix.display();};

	void dijkstra(void)
	{
		cout << vertices_amount;
		cout << "Dijkstra" << endl;
		Vertex* v = V_tmp;
		Vertex* tmp;

		int U_idx = vertices_amount - 1;
		int distance[vertices_amount];
		int locator[vertices_amount];
		Vertex* map[vertices_amount];

		priority_queue<int, int> Q(vertices_amount);

		for(auto u = vertex_list.begin(); u != vertex_list.end(); u++) //For all Vertices in Graph
		{
			map[U_idx] = *u;						//Remap!!
			tmp = *u;
			cout << "debug " << tmp->idx << "u_idx" << U_idx << endl;

			if(*u == v)
				distance[U_idx] = 0;									//Initialize D[v] = 0
			else
				distance[U_idx] = 2000000;								//Initialize D[u] = inf

			locator[U_idx] = Q.insert(distance[U_idx], U_idx);		//Let a priority queue Q contain all the vertices of G using the D labels as keys

			U_idx--;
		}

		cout << "inicjalizacja D[u]" << endl;
		for(int idx_tmp = 0; idx_tmp < U_idx; idx_tmp++)
			cout << distance[idx_tmp] << endl;
		cout << "Kopiec: " << endl;
				Q.display();

		while(!Q.empty())
		{
			auto u = Q.removeMin();
			cout << "UUUUUUUUUUUUU" << u << endl;

			for(int e = 0; e < vertices_amount; e++)	//for all e e G.indicentEdges(u)
			{

				Edge** e_val = incidentEdges(map[u]);

				if(e_val[e] != 0)
				{
					cout << e_val[e] << endl;
					Vertex* z = opposite(map[u], e_val[e]);

					int r = distance[u] + e_val[e]->weight;
					if(r < distance[z->idx])
					{
						cout << u << " d(u) " << distance[u] << " eval e: " << e_val[e]->weight << " distance z "<<distance[z->idx] << " r " << r << endl;
						distance[z->idx] = r;

						Q.replaceKey(locator[z->idx], z->idx);
					}
				}

			}
		}

		for(int i = 0; i < vertices_amount; i++)
			cout << "i " << i << " D(i) " << distance[i] << endl;
	}

	GraphAdjMx(FILE* imp_file)
	{
		vertices_amount = 0;
		int E_amount, V_amount, V_start;
		int V_first, V_second, E_weight;

		fscanf(imp_file, "%d %d %d", &E_amount, &V_amount, &V_start);
		cout << "Start: " << "E: "<< E_amount << " V: " << V_amount << " V2: "<< V_start << endl;

		Vertex* V_curr[V_amount];
		for(int i = 0; i < V_amount; i++)
			 V_curr[i] = insertVertex(i);
		V_tmp = V_curr[V_start];

		for(int i = 0; i < E_amount; i++)
		{
			fscanf(imp_file, "%d %d %d", &V_first, &V_second, &E_weight);
			cout << " i: " << i << " V: " << V_first << " V2: " << V_second << " E: " << E_weight << endl;
			insertEdge(V_curr[V_first], V_curr[V_second], E_weight);
		}

	}

	struct Vertex
	{
		W data;
		int idx;
	};

	struct Edge
	{
		T weight;
		struct Vertex* vertex_start;
		struct Vertex* vertex_end;
	};
};




#endif /* GRAPH_ADJMATRIX_HPP_ */
