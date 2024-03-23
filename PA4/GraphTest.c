//-----------------------------------------------------------------------------
// Andy Choi
// achoi15
// pa4
// 
// GraphTest.c
// Test file for Graph ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"


int main(int argc, char* argv[]){
	int n = 6, s = 2 , u = 3;
	Graph A = newGraph(n);
 
	//Build graph G 
	// A = newGraph(n);
	// List L = newList();
	// List C = newList();	


	// addArc(A, 64, 4);
 //    addArc(A, 64, 3);
 //    addArc(A, 42, 2);
 //    addArc(A, 2, 64);
 //    addArc(A, 4, 2);
 //    addArc(A, 3, 42);
 //    BFS(A, 3);
 //    getPath(L, A, 64);
 //    append(C, 3);
 //    append(C, 42);
 //    append(C, 2);
 //    append(C, 64);
 //    printf("List L: ");
 //    printList(stdout, L);
 //    printf("List C: ");
 //    printList(stdout, C);
 //    if (!equals(L, C)) return 1;

 //    moveFront(L);
 //    BFS(A, 2);

 //    getPath(L, A, 2);
 //    // printGraph(stdout, A);
 //    append(C, 2);

 //    printf("List L3: ");
 //    printList(stdout, L);

 //    printf("List C3: ");
 //    printList(stdout, C);
 //    if (!equals(L, C)) return 2;

 //    getPath(L, A, 99);

 //    printf("List L4: ");
 //    printList(stdout, L);

 //    printf("List C4: ");
 //    printList(stdout, C);
 //    if (equals(L, C)) return 3;

	addEdge(G, 1, 2); addEdge(G, 1, 3);
	addEdge(G, 2, 1); addEdge(G, 2, 4);
	addEdge(G, 2, 5); addEdge(G, 2, 6); 
	addEdge(G, 3, 1); addEdge(G, 3, 4); 
	addEdge(G, 4, 2); addEdge(G, 4, 3);
	addEdge(G, 4, 5); addEdge(G, 5, 2);
	addEdge(G, 5, 4); addEdge(G, 5, 6);
	addEdge(G, 6, 2); addEdge(G, 6, 5);

	// Print adjacency list representation of G
	printGraph(stdout, G);


	printf("\nOrder: %d\n", getOrder(G));
	printf("Size: %d\n", getSize(G));
	printf("Source: %d\n\n", getSource(G));

	printf("Run BFS\n");
	BFS(G, s);
	printf("Source: %d\n", getSource(G));
	printf("Distance %d to %d: %d\n",u, s, getDist(G, u));
	printf("Parent of %d: %d\n",u, getParent(G, u));

	List L = newList();
	getPath(L, G, u);
	printf("Shortest %d-%d path is: ",s, u);
	printList(stdout, L);
	printf("\n\n");


	List S = newList();
	printf("Source: %d\n", getSource(G));
	getPath(S, G, s);
	printf("Distance %d to %d: %d\n",s, s, getDist(G, s));
	printf("Parent of %d: %d\n",s, getParent(G, s));
	printf("Shortest %d-%d path is: ",s, s);
	printList(stdout, S);
	printf("\n");

	printf("\nAdd Arc 4 to 1\n");
	addArc(G, 1, 4);
	printGraph(stdout, G);

	printf("\nAdd Arc 5 to 3\n");
	addArc(G, 3, 5);
	printGraph(stdout, G);

	printf("\nmakeNULL()\n");
	makeNull(G);
	printGraph(stdout, G);

	printf("\nOrder: %d\n", getOrder(G));
	printf("Size: %d\n", getSize(G));
	printf("Source: %d\n", getSource(G));
	printf("Distance %d to %d: %d\n",s, u, getDist(G, u));
	printf("Parent of %d: %d\n",u, getParent(G, u));

	// Free objects
	freeList(&S); 
	freeList(&L); 
	freeGraph(&G);

	return(0);
}
/*
1: 2 3
2: 1 4 5 6
3: 1 4
4: 2 3 5
5: 2 4 6
6: 2 5

Order: 6
Size: 16
Source: -2

Run BFS
Source: 2
Distance 3 to 2: 2
Parent of 3: 1
Shortest 2-3 path is: 2 1 3

Source: 2
Distance 2 to 2: 0
Parent of 2: -2
Shortest 2-2 path is: 2

Add Arc 4 to 1
1: 2 3 4
2: 1 4 5 6
3: 1 4
4: 2 3 5
5: 2 4 6
6: 2 5

Add Arc 5 to 3
1: 2 3 4
2: 1 4 5 6
3: 1 4 5
4: 2 3 5
5: 2 4 6
6: 2 5

makeNULL()
1:
2:
3:
4:
5:
6:

Order: 6
Size: 0
Source: -2
Distance 2 to 3: -1
Parent of 3: -2
*/