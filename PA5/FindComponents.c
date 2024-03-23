//-----------------------------------------------------------------------------
// Andy Choi
// achoi15
// pa5
// 
// FindComponents.c
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

	// add arcs to graph until u and v == 0
	int u, v;
	while(fscanf(in, "%d %d", &u, &v) == 2){
		if(u == 0 && v == 0) 
			break;
		
		addArc(G, u, v);
	}

	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);

	// fprintf(stdout, "hi\n");


	// fill S with arbitrary values for dfs
	List S = newList();
	for(int i = 1; i <= getOrder(G); i++) {
		append(S, i);
	}

	// Run DFS
	DFS(G, S);

	// Set T as transpose of G	
	Graph T = transpose(G);

	// fprintf(stdout, "hi2\n");
	DFS(T, S);

	int scc = 0; // number of strongly connected components

	// determine # scc by comparing parents to nil
	moveFront(S);
	while(index(S) != -1){
		if( getParent(T, get(S)) == NIL){
			scc++;
		}

		moveNext(S);
	}

	// create list of sccs
	List sccL[scc];
	for(int i = 0; i < scc; i++){
	   sccL[i] = newList();
	}

	// printf("\nscc: %d\n", scc);

	moveFront(S);
	int indx = scc; // indx is the index of num of components

	// appends vertices to indx until parent is NIL
	while(index(S) != -1){
	    if( getParent(T, get(S)) == NIL)
	        indx--;

	    if(scc == indx)
	        break;

	   append(sccL[indx], get(S));
	   moveNext(S);
	}

	// printList(stdout, S);
	// printf("\nscc: %d\n", scc);


	fprintf(out, "\nG contains %d strongly connected components:\n", scc);

	// outputs components with their respective scc list
	for(int i = 0; i < scc; i++){
		fprintf(out, "Component %d: ", i + 1);
		// printf("hi\n");

		printList(out, sccL[i]);
		fprintf(out, "\n");

		freeList(&(sccL[i]));
	}


	// free objects
	freeGraph(&G);
	freeGraph(&T);
	freeList(&S);


	fclose(in);
	fclose(out);

	return 0;
}