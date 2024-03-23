//-----------------------------------------------------------------------------
// Andy Choi
// achoi15
// pa5
// 
// Graph.c
// Implementation file for Graph ADT, Depth First Search (DFS)
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

typedef struct GraphObj{
	List *L; // array of list ith element contains the neighbors of vertex i.
	int *color; // array of ints representing color w,b,g
	int *p; // array of ints of parents
	int *d; // array of ints of discover times
	int *f; // array of ints of finish times
	int size; // number of edges, size
	int order; // vertices, order of the graph
} GraphObj;

typedef enum color{
	WHITE,
	GRAY,
	BLACK
}color;

/*** Constructors-Destructors ***/
Graph newGraph(int n){
	if(n < 1){
		printf("Graph Error: calling newGraph() with order < 1.\n");
		exit(1);
	}

	Graph G = malloc(sizeof(GraphObj));

	G->L = calloc(n + 1, sizeof(List));;
	G->color = malloc((n + 1)*sizeof(int));
	G->p = malloc((n + 1)*sizeof(int));
	G->d = malloc((n + 1)*sizeof(int));
	G->f = malloc((n + 1)*sizeof(int));


	G->size = 0;
	G->order = n;

	G->L[0] = NULL; // set L[0] to null as it will not be used.

	//sets DFS fields
	for(int i = 1; i <= n; i++){
		G->L[i] = newList();
		G->p[i] = NIL;
		G->d[i] = UNDEF;
		G->f[i] = UNDEF;		
		G->color[i] = WHITE;
	}

	return(G);
}

void freeGraph(Graph* pG){

	// free list memory
	for(int i = 1; i <= getOrder(*pG); ++i){
		freeList(&(*pG)->L[i]);
	}

	// free all heap memory associated with *pG
	free((*pG)->L);
	free((*pG)->color);
	free((*pG)->p);
	free((*pG)->d);
	free((*pG)->f);

	
	//set pointers to NULL
	(*pG)->L = NULL;
	(*pG)->color = NULL;
	(*pG)->p = NULL;
	(*pG)->d = NULL;
	(*pG)->f = NULL;

	if(pG!=NULL && *pG!=NULL){
		free(*pG);
		*pG = NULL;
	}
}

/*** Access functions ***/
int getOrder(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getOrder() on NULL Graph pointer.\n");
		exit(1);
	}else
		return(G->order);
}

int getSize(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getSize() on NULL Graph pointer.\n");
		exit(1);
	}else
		return(G->size);
}

int getParent(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: calling getParent() on NULL Graph pointer\n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getParent() with index less than 1 or greater than order.\n");
		exit(1);
	}else
		return(G->p[u]);
}

int getDiscover(Graph G, int u){
	if(G == NULL) {
		printf("Graph Error: calling getDiscover() on NULL Graph pointer\n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getDiscover() with index less than 1 or greater than order.\n");
		exit(1);
	}else
		return(G->d[u]);
}

int getFinish(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: calling getFinish() on NULL Graph pointer.\n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getFinish() with index less than 1 or greater than order.\n");
		exit(1);
	}else
		return(G->f[u]);
}


/*** Helper Functions ***/
// insertOrdered() 
// function for inserting x into list A
// in ascending order
void insertOrdered(List A, int x){
	
	//appends first x value when list is empty
	if(isEmpty(A)){
		append(A, x);
	}

	moveFront(A);
	while(index(A) != -1){
		int temp = get(A);
		// printf("temp: %d\n", temp);

		if(x == temp){
			moveNext(A);
			break;
		}
		// when x is less than temp, insert before x
		if(x < temp){
			insertBefore(A, x);
			moveNext(A);
			break;
		}
		// at the end of list, append last x 
		if(index(A) == length(A) - 1){
			append(A, x); 
		}

		moveNext(A);
	}
}

// Visit() 
// recursive algorithm for discovering and finishing x
// inputs time which points to time address in DFS()
void Visit(Graph G, List S, int x, int *time){

	if(G == NULL){
		printf("Graph Error: calling Visit() on NULL Graph pointer\n");
		exit(1);
	}

	if(S == NULL){
		printf("Graph Error: calling Visit() on NULL List pointer\n");
		exit(1);
	}

	if(x < 0){
		printf("Graph Error: calling DFS() on negative x\n");
		exit(1);
	}

	
	G->d[x] = ++(*time); // discover x
	G->color[x] = GRAY;
	
	List adj = G->L[x];

	moveFront(adj);
	// fprintf(stdout, "heee\n");
	while(index(adj) != -1){
		int y = get(adj);

		if(G->color[y] == WHITE){
			G->p[y] = x;
			Visit(G, S, y, time);
		}
		moveNext(adj);
	}

	G->color[x] = BLACK;
	G->f[x] = ++(*time); // finish x

	prepend(S, x); // push x into finish list
}


/*** Manipulation procedures ***/
void makeNull(Graph G){
	if(G == NULL) {
		printf("Graph Error: calling makeNull() on NULL Graph pointer\n");
		exit(1);
	}

	// clear edges, and reset BFS fields
	for(int i = 1; i <= getOrder(G); i++) {
		clear(G->L[i]);
		G->p[i] = NIL;
		G->d[i] = UNDEF;
		G->f[i] = UNDEF;		
		G->color[i] = WHITE;
	}

	G->size = 0;
}

//inserts a new edge joining u to v
void addEdge(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: calling addEdge() on NULL Graph pointer\n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
		printf("Graph Error: calling addEdge() with indices not in the range of 1 to the order of G.\n");
		exit(1);
	}
	if(u == v){
		printf("Graph Error: calling addEdge() when u == v.\n");
		exit(1);
	}

	//v is added to the adjacency List of u
	List U = G->L[u];
	insertOrdered(U, v);

	//u is added to the adjacency List of v
	List V = G->L[v];
	insertOrdered(V, u);

	G->size++;
}

//inserts a new directed edge from u to v
void addArc(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: calling addArc() on NULL Graph pointer\n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
		printf("Graph Error: calling addArc() with indices not in the range of 1 to the order of G.\n");
		exit(1);
	}

	//v is added to the adjacency List of u
	List U = G->L[u];
	insertOrdered(U, v);

	G->size++;
}

void DFS(Graph G, List S){

	if(G == NULL){
		printf("Graph Error: calling DFS() on NULL Graph pointer\n");
		exit(1);
	}

	if(S == NULL){
		printf("Graph Error: calling DFS() on NULL List pointer\n");
		exit(1);
	}

	if(length(S) != getOrder(G)){
		printf("Graph Error: calling DFS() with length of List S != order of G.\n");
		exit(1);
	}
	
	//setting the color, parent, discover, and finish fields of G
	for(int i = 1; i <= getOrder(G); i++) {
		G->color[i] = WHITE;
		G->p[i] = NIL;
		G->d[i] = UNDEF;
		G->f[i] = UNDEF;		
	}

	int time = 0;

	List C = copyList(S); // set C as a copy of S


	clear(S); // reset S to add finish times

	moveFront(C);
	while(index(C) != -1){
		int x = get(C);
		if(G->color[x] == WHITE){
			Visit(G, S, x, &time);
		}
		moveNext(C);
		// printf("\nx: %d \n", x);
		// printf("d: %d \n", getDiscover(G, x));
		// printf("f: %d \n", getFinish(G, x));
	}

	// printList(stdout, C);

	freeList(&C);
}

/*** Other operations ***/

Graph transpose(Graph G){
	if(G == NULL){
		printf("Graph Error: calling transpose() on NULL Graph reference\n");
		exit(1);
	}

	Graph T = newGraph(getOrder(G));

	for(int i = 1; i <= getOrder(G); i++){

		List tL = G->L[i];

		moveFront(tL);
		while(index(tL) != -1){
			int x = get(tL);
			addArc(T, x, i); // switch rows with columns

			moveNext(tL);
		}
	}

	return(T);
}

Graph copyGraph(Graph G){

	if(G == NULL){
		printf("Graph Error: calling copyGraph() on NULL Graph reference\n");
		exit(1);
	}

	Graph C = newGraph(getOrder(G));

	C->L[0] = NULL; // set L[0] to null as it will not be used.

	for(int i = 1; i <= getOrder(G); i++){
		List cL = G->L[i];

		moveFront(cL);
		while(index(cL) != -1){
			int x = get(cL);

			addArc(C,i,x);

			moveNext(cL);
		}
	}


	return(C);

}

void printGraph(FILE* out, Graph G){
	if(out == NULL){
		printf("Graph Error: calling printGraph() on NULL file* reference\n");
		exit(1);
	}
	if(G == NULL){
		printf("Graph Error: calling printGraph() on NULL Graph reference\n");
		exit(1);
	}

	for(int i = 1; i <= getOrder(G); i++){
		fprintf(out,"%d: ",i);
		printList(out, G->L[i]);
		fprintf(out, "\n");
	}
}
