#include "Graph.h"
#include "AdjMatrix.h"
#include <ctime>
using namespace std;

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

void importGraphFromFile(FILE* f)
{
	int V, edges, source, src, dest, weight;

		fscanf(f, "%d %d %d", &edges, &V, &source);
		Graph g(V);
		for(int i = 0; i < edges; i++)
		{
			fscanf(f, "%d %d %d", &src, &dest, &weight);
			g.addEdge(src, dest, weight);
		}
}

void testing()
{
    FILE* file;
    clock_t start;
    clock_t stop;
    double time;
	int V[] = {500, 625, 750, 875, 1000};
	float denisty[] = {0.25, 0.5, 0.75, 1};

	file = file_open("F:\\Programowanie\\Eclipse_Workspace\\PAMSI_05\\wyniki.txt", "w+");
	for(int a = 0; a < 2; a++)
	{
		switch(a)
		{
		case 0: {fprintf(file,"************************ LIST ************************ \n"); break;}
		case 1: {fprintf(file,"************************  MATRIX ************************ \n"); break;}
		}
		for(int i = 0; i < 5; i++)
			{

				fprintf(file, "______________ V = %d ___________\n", V[i]);
				cout << "\n______________ V = "<< V[i] << "___________\n";
				for(int j = 0; j < 4; j++)
				{
					fprintf(file, "__________ denisty = %f _________ \n", denisty[j]);
					cout << "\n__________ denisty = " << denisty[j] << " _________ \n";
					for(int k = 0; k < 100; k++)
					{
						switch(a)
						{
						case 0:
						{
							Graph g(V[i]);
							g.fillGraph(denisty[j]);
							start = clock();
							g.dijkstra(0);
							stop = clock();
							time = (double)(stop-start) / CLOCKS_PER_SEC;
							fprintf(file, "%f \n", time);
							cout << "->";
							break;

							AdjMatrix m(V[i]);
							m.fill(denisty[j]);
							start = clock();
							m.dijkstra(0);
							stop = clock();
							time = (double)(stop-start) / CLOCKS_PER_SEC;
							fprintf(file, "%f \n", time);
							cout << "**>";
							break;
						}
						case 1:
						{
							AdjMatrix m(V[i]);
							m.fill(denisty[j]);
							start = clock();
							m.dijkstra(0);
							stop = clock();
							time = (double)(stop-start) / CLOCKS_PER_SEC;
							fprintf(file, "%f \n", time);
							cout << "**>";
							break;
						}
						}
					}
					fprintf(file, "\n");
				}
				fprintf(file,"\n");
			}

	}

}


int main()
{
	srand( time( NULL ) );


testing();


	return 0;
}
