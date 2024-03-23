//-----------------------------------------------------------------------------
// Andy Choi
// achoi15
// pa4
//
// List.c
// C file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
	int data;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;

	int length;
	int index;

} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next, prev, and data fields.
// Private.
Node newNode(int data){
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return N;
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN != NULL && *pN != NULL ){
		free(*pN);
		*pN = NULL;
   }
	return;
}

// newList()
// Returns reference to new empty List object.
List newList(void){
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = 0;
	return L;
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
		while( !isEmpty(*pL) ) { 
		   deleteFront(*pL); 
		}
		free(*pL);
		*pL = NULL;
   }
	return;
}

// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L){
	if( L==NULL ){
		printf("List Error: calling length() on NULL List reference\n");
		exit(1);
	}

   return(L->length);
}

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L){

	if( L==NULL ){
		printf("List Error: calling isEmpty() on NULL List reference\n");
		exit(1);
	}

	return(L->length==0);
}

 // Returns index of cursor element if defined, -1 otherwise.
int index(List L){

	if( L==NULL ){
		printf("List Error: calling index() on NULL List reference\n");
		exit(1);
	}

	if (L->cursor == NULL){
		return -1;
	}
	
	return(L->index);
}

int front(List L){// Returns front element of L. Pre: length()>0
	if( L==NULL ){
		printf("List Error: calling front() on NULL List reference\n");
		exit(1);
	}

	if (length(L) < 0){
		printf("List Error: calling front() on List with length() < 0\n");
		exit(1);
	}

	return(L->front->data);
}


int back(List L){// Returns back element of L. Pre: length()>0
	if( L==NULL ){
		printf("List Error: calling back() on NULL List reference\n");
		exit(1);
	}
	if (length(L) < 0){
		printf("List Error: calling back() on List with length() < 0\n");
		exit(1);
	}

	return(L->back->data);
}

int get(List L){ // Returns cursor element of L. Pre: length()>0, index()>=0

	if(L == NULL){
		printf("List Error: calling get() on NULL List reference\n");
		exit(1);
	}

	if( index(L) < 0 ){
		printf("List Index Error: calling get() on an undefined cursor\n");
		exit(1);
	}

	if( (length(L) < 0) ){
		printf("List Error: calling get() on List with length() < 0\n");
		exit(1);
	}
	return(L->cursor->data);
}

// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
int equals(List A, List B){
    int eq = 0;
    Node N = NULL;
    Node M = NULL;

    if( A==NULL || B==NULL ){
        printf("List Error: calling equals() on NULL List reference\n");
        exit(1);
    }

    eq = ( A->length == B->length );
    N = A->front;
    M = B->front;

    while( eq && N!=NULL){
        eq = (N->data==M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
 }

// Manipulation procedures --------------------------------------------------------


// Resets L to its original empty state.
void clear(List L){
	
	moveFront(L);

	while(!isEmpty(L)){
		deleteFront(L);
	}
	L->index = -1;

	return;
}

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){

	if (!isEmpty(L)){
		L->cursor = L->front;
		L->index = 0;
		// printf("%d", L->cursor->data);
	}
	return;
}

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L){

	int len = length(L) - 1;

	if(!isEmpty(L)){
		L->cursor = L->back;
		L->index = len;
	}

	return;
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; 
// if cursor is defined and at front, cursor becomes undefined; 
//if cursor is undefined do nothing
void movePrev(List L){

	if(L->cursor != NULL){
		if(L->cursor != L->front){
			L->cursor = L->cursor->prev;
			L->index--;
			// printf("%d", L->cursor->prev->data);
		}else{ // cursor is front
			L->cursor = NULL;
			L->index = -1;
		}
	}

	return;
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){

	if(L->cursor != NULL){
		if (L->cursor != L->back){
			L->cursor = L->cursor->next;
			L->index++;
			// printf("%d", L->cursor->prev->data);
		}else{ // cursor is back
			L->cursor = NULL;
			L->index = -1;
		}
	}

	return;
	// printf("%d", L->cursor->data);
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int data){

	if(L == NULL){
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(1);
	}

	Node N = newNode(data);

	if(N == NULL){
		printf("malloc Error: calling prepend() - failed to allocate storage\n");
		exit(1);
	}

	N->next = L->front;
	N->prev = NULL; 

	if( isEmpty(L) ) { 
		L->back = N; 
		L->cursor = N;
	}else{ 
		L->front->prev = N;
	}

	L->front = N;
	L->index++;
	L->length++;
	return;
}


// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int data){
	if(L == NULL){
		printf("List Error: calling append() on NULL List reference\n");
		exit(1);
	}

	Node N = newNode(data);

	if(N == NULL){
		printf("malloc Error: calling append() - failed to allocate storage\n");
		exit(1);
	}
	N->prev = L->back; 
	N->next = NULL;


	if( isEmpty(L) ) { 
		N->prev = NULL; 
		L->front = N;
		L->index++;
		L->cursor = N;
	}else{ 
		L->back->next = N;
		N->prev = L->back;
	}

	L->back = N; 
	L->length++;
	return;
} 

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){

	if( L == NULL ){
		printf("List Error: calling insertBefore() on NULL List reference\n");
		exit(1);
	}

	if( isEmpty(L) ){
		printf("List Error: calling insertBefore() on an empty List\n");
		exit(1);
	}

	if( index(L) < 0 ){
		printf("List Index Error: calling insertBefore() on an undefined cursor\n");
		exit(1);
	}

	// when cursor is the front node, prepend
	if(L->cursor == L->front) {
		prepend(L, data);
	}else{
		Node N = newNode(data);

		L->cursor->prev->next = N;

		N->next = L->cursor;
		N->prev = L->cursor->prev;
		L->cursor->prev = N;

		L->length++;

	}
	return;
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
	
	if( L == NULL ){
		printf("List Error: calling insertAfter() on NULL List reference\n");
		exit(1);
	}
	if( isEmpty(L) ){
		printf("List Error: calling insertAfter() on an empty List\n");
		exit(1);
	}

	if( index(L) < 0 ){
		printf("List Index Error: calling insertAfter() on an undefined cursor\n");
		exit(1);
	}

	Node N = newNode(data);

	// if cursor is the back node, append
	if(L->cursor == L->back) {
		append(L, data);
	}
	else{
		N->next = L->cursor->next;
		N->prev = L->cursor;
		L->cursor->next = N;
		L->length++;		
	}
	return;
}

// deleteFront()
// Delete the front element. Pre: length()>0
// Pre: !isEmpty(L)
void deleteFront(List L){ 

	if( L==NULL ){
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(1);
	}
	if( isEmpty(L) ){
		printf("List Error: calling deleteFront() on an empty List\n");
		exit(1);
	}

	// node to be deleted
	Node N = L->front;

	if(N == L->cursor){
		L->cursor = NULL;
		L->index = -1;
	}


	// move the next address of the front node to 2nd first node
	L->front = L->front->next; 

	freeNode(&N);
	L->length--;

	// if new front node is not null, set the prev addr of front node to null
	if(L->front != NULL) L->front->prev = NULL;

	return;
}

// Delete the back element. Pre: length()>0
void deleteBack(List L){ 

	if( L==NULL ){
		printf("List Error: calling deleteBack() on NULL List reference\n");
		exit(1);
	}
	if( isEmpty(L) ){
		printf("List Error: calling deleteBack() on an empty List\n");
		exit(1);
	}

	Node N = L->back;
	if(N == L->cursor){
		L->cursor = NULL;
		L->index = -1;
	}
	
	// move previous address of back node to 2nd last node
	L->back = L->back->prev;


	freeNode(&N);
	L->length--;

	// if back node is not null, set the next address of back node to null
	if(L->back != NULL) L->back->next = NULL;

	return;
}


// Delete cursor element, making cursor undefined.
//Pre: length()>0, index()>=0
void delete(List L){

	if( L==NULL ){
		printf("List Error: calling delete() on NULL List reference\n");
		exit(1);
	}

	if( isEmpty(L) ){
		printf("List Error: calling delete() on an empty List\n");
		exit(1);
	}

	if( index(L) < 0 ){
		printf("List Index Error: calling delete() on an undefined cursor\n");
		exit(1);
	}


	Node N = L->cursor;

	// if node to be deleted is the front node
	if(L->front == N){
		L->front = N->next; 
		L->front->prev = NULL; 
	}
	else if(L->back == N){ // if the node is the back node
		L->back = N->prev; // prev node will be the last node
		L->back->next = NULL;
	}
	else{ 
		N->next->prev = N->prev; // next node's prev points to N's prev
		N->prev->next = N->next; // prev node's next points to N's next
	}
  
	L->cursor = NULL;
	L->length--;

	freeNode(&N);

	return;
}


//-------------------------------------------------------------------------------
// printList()
void printList(List L){
	if(L == NULL){
		printf("List Error: calling printList() on NULL List reference\n");
		exit(1);
	}

	Node N = L->front;

	while(N != NULL){
		printf("%d", N->data);
		N = N->next;

		if(N != NULL) printf(" ");
	}
	// printf("\n");
	return;

}
// Prints data elements in L on a single line to stdout.
// void printList(FILE* out, List L){
// 	if(out == NULL){
// 		printf("List Error: calling printList() on NULL file* reference\n");
// 		exit(1);
// 	}
// 	if(L == NULL){
// 		printf("List Error: calling printList() on NULL List reference\n");
// 		exit(1);
// 	}

// 	Node N = L->front;

// 	while(N != NULL){
// 		fprintf(out, "%d", N->data);
// 		N = N->next;

// 		if(N != NULL)
// 			fprintf(out, " ");
// 	}
// 	// printf("\n");

// }

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){

	if( L==NULL ){
		printf("List Error: calling copyList() on NULL List reference\n");
		exit(1);
	}

	Node N = NULL;
	List nList = newList();

	for(N = L->front; N != NULL; N = N->next){
		append(nList, N->data);
	}

	return nList;
}
