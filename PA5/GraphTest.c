//-----------------------------------------------------------------------------
// Andy Choi
// achoi15
// pa5
// 
// GraphTest.c
// Test file for Graph ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"


int main(int argc, char* argv[]){
	int n = 8;
	Graph G = newGraph(n);
 
	//Build graph G 
	// List C = newList();	

	addArc(G, 1, 2);
	addArc(G, 1, 5);

	addArc(G, 2, 5); addArc(G, 2, 6);
	addArc(G, 3, 4); addArc(G, 3, 7); addArc(G, 3, 8); addArc(G, 3, 6); addArc(G, 3, 2);   
	addArc(G, 6, 7);
	addArc(G, 6, 5); 
	addArc(G, 8, 7);
	addArc(G, 8, 4);


	// Print adjacency list representation of G
	printGraph(stdout, G);

	// fill S with values
	List S = newList();
	for (int i = 1; i <= getOrder(G); i++){
		append(S, i);
	}

	DFS(G, S);

	printf("\n");
	int u = 3;
	printf("u: %d\n", u);
	printf("Discover: %d\n", getDiscover(G, u));
	printf("Finish: %d\n", getFinish(G, u));
	printf("Parent: %d\n", getParent(G, u));
	printf("Order: %d\n", getOrder(G));
	printf("Size: %d\n", getSize(G));

	printf("Parent of 5: %d\n", getParent(G, 5));

	// Set T as transpose of G	
	// Graph T = transpose(G);

	// fprintf(stdout, "hi2\n");
	// DFS(T, S);

	printf("Finish times: ");
	printList(stdout, S);
	printf("\n");


	printf("\nTranspose:\n");
	Graph T = transpose(G);
	printGraph(stdout, T);


	printf("\nCopy:\n");
	Graph C = transpose(G);
	printGraph(stdout, C);

	printf("\nmakeNull:");
	makeNull(G);
	printf("\n");
	printGraph(stdout, G);


	freeGraph(&G);
	// freeGraph(&T);
	// freeGraph(&C);


	return(0);
}
/*
1: 2 5
2: 5 6
3: 2 4 6 7 8
4:
5:
6: 5 7
7:
8: 4 7

u: 3
Discover: 11
Finish: 16
Parent: -2
Order: 8
Size: 13
Parent of 5: 2
Finish times: 15 7 8 4 13 16 9 10

Transpose:
1:
2: 1 3
3:
4: 3 8
5: 1 2 6
6: 2 3
7: 3 6 8
8: 3

Copy:
1:
2: 1 3
3:
4: 3 8
5: 1 2 6
6: 2 3
7: 3 6 8
8: 3

makeNull:
1:
2:
3:
4:
5:
6:
7:
8:

*/