//-----------------------------------------------------------------------------
// Andy Choi
// achoi15
// pa4
// 
// FindPath.c
// Client file for Graph ADT
// Configured from FileIO.c
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "Graph.h"

int main(int argc, char const *argv[]){
	FILE *in, *out;

	// check command line for correct number of arguments
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	// open files for reading and writing 
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if( out==NULL ){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}


	// grabs the order and creates new graph 
	int n;
	fscanf(in, "%d", &n);
	Graph G = newGraph(n);

	// add edges to graph until u and v == 0
	int u, v;
	while(fscanf(in, "%d %d", &u, &v) == 2){
		if(u == 0 && v == 0) 
			break;
		
		addEdge(G, u, v);
	}

	printGraph(out, G);

	int s, dest; // source and destination
	List L = newList();

	while(fscanf(in, "%d %d", &s, &dest)){
		if(s == 0 && dest == 0)
			break;

		BFS(G, s);
		getPath(L, G, dest);

		fprintf(out, "\nThe distance from %d to %d is ", s, dest);

		// no path exists if s is NIL or distance is INF
		if(s == NIL || getDist(G, dest) == INF){
			fprintf(out, "infinity\n");
			fprintf(out, "No %d-%d path exists\n", s, dest);
		}else{
			fprintf(out, "%d\n", getDist(G, dest));
			fprintf(out, "A shortest %d-%d path is: ", s, dest);
			printList(out, L);
			fprintf(out, "\n");
		}

		// clear list for next path
		clear(L);
	}

	// free objects
	freeList(&L);
	freeGraph(&G);

	fclose(in);
	fclose(out);

	return 0;
}