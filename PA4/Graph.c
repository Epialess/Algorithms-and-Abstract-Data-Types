//-----------------------------------------------------------------------------
// Andy Choi
// achoi15
// pa4
// 
// Graph.c
// Implementation file for Graph ADT, Breadth First Search
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

typedef struct GraphObj{
	List *L; // array of list ith element contains the neighbors of vertex i.
	int *color; // array of ints representing color w,b,g
	int *p; // array of ints of parents
	int *d; // array of ints of distance from source
	int size; // number of edges
	int order; // vertices, order of the graph
	int source; // source of graph
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

	G->size = 0;
	G->order = n;
	G->source = NIL;

	G->L[0] = NULL; // set L[0] to null as it will not be used.

	//sets BFS fields
	for(int i = 1; i <= n; i++){
		G->L[i] = newList();
		G->p[i] = NIL;
		G->d[i] = INF;
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
	
	//set pointers to NULL
	(*pG)->L = NULL;
	(*pG)->color = NULL;
	(*pG)->p = NULL;
	(*pG)->d = NULL;

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

int getSource(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getSource() on NULL Graph pointer.\n");
		exit(1);
	}else
		return(G->source); //returns NIL if calling before BFS 
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
		return(G->p[u]); //returns NIL if calling before BFS 
}

int getDist(Graph G, int u){
	if(G == NULL) {
		printf("Graph Error: calling getDist() on NULL Graph pointer\n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getDist() with index less than 1 or greater than order.\n");
		exit(1);
	}else
		return(G->d[u]);
}

void getPath(List L, Graph G, int u){
	if(getSource(G) == NIL) {
		printf("Graph Error: calling getPath() before BFS().\n");
		exit(1);
	}

	// case if u is the source vertex
	if(G->source == u){
		append(L, u);
	}else if(G->p[u] == NIL){ // if u doesnt have a path, clear any previous list and append NIL to L 
		clear(L);
		append(L, NIL);
		return;
	}else{  // when the parent of u is not NIL, call getpath and append u to list L 
		getPath(L, G, G->p[u]);
		append(L, u);
	}

}


/*** Helper Functions ***/
// deQueue()
// function for dequeueing in BFS() 
// returns and remove front of list
int deQueue(List A) {
	if(A == NULL){
		printf("Graph Error: calling deQueue() on NULL List pointer.\n");
		exit(1);
	}
	if(isEmpty(A)){
		printf("Graph Error: calling deQueue() on empty list.\n");
		exit(1);
	}

	int f = front(A);
	deleteFront(A);
	return(f);
}

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
		G->d[i] = INF;
		G->color[i] = WHITE;
	}

	G->source = NIL;

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


void BFS(Graph G, int s){

	if(G == NULL){
		printf("Graph Error: calling BFS() on NULL Graph pointer\n");
		exit(1);
	}
	if(s < 1 || s > getOrder(G)){
		printf("Graph Error: calling BFS() with a source less than 1 or greater than the order of G.\n");
		exit(1);
	}
	
	//setting the color, distance, parent, and source fields of G
	for(int i = 1; i <= getOrder(G); i++) {
		G->color[i] = WHITE;
		G->p[i] = NIL;
		G->d[i] = INF;
	}

	G->source = s;
	G->color[s] = GRAY;
	G->d[s] = 0;
	G->p[s] = NIL;
	List Q = newList(); // let list Q be a queue
	append(Q, s); // enqueue source

	while(!isEmpty(Q)){
		int x = deQueue(Q); // dequeue source vertex
		List X = G->L[x];

		moveFront(X);
		while(index(X) != -1){
			int y = get(X);

			if(G->color[y] == WHITE){
				G->color[y] = GRAY;
				G->d[y] = G->d[x] + 1;
				G->p[y] = x;
				append(Q, y);
			}

			moveNext(X);
		}
		G->color[x] = BLACK;
	}

	freeList(&Q);
}

/*** Other operations ***/
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
