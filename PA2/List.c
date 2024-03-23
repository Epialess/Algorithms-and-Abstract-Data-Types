//-----------------------------------------------------------------------------
// Andy Choi
// achoi15
// pa2
//
// List.c
// C file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Matrix.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
	void* data;
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
Node newNode(void* data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN != NULL && *pN != NULL ){
	    free(*pN);
	    *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = 0;
    return(L);
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

	if (L->cursor == NULL){
		return -1;
	}
	else
		return(L->index);
}

void* front(List L){// Returns front element of L. Pre: length()>0
	if( L==NULL ){
		printf("List Error: calling front() on NULL List reference\n");
		exit(1);
    }

	if (length(L) < 0){
		printf("List Error: calling front() on List with length() < 0\n");
		exit(1);
	}

	return (L->front->data);
}


void* back(List L){// Returns back element of L. Pre: length()>0
	if( L==NULL ){
		printf("List Error: calling back() on NULL List reference\n");
		exit(1);
    }
	if (length(L) < 0){
		printf("List Error: calling back() on List with length() < 0\n");
		exit(1);
	}

	return (L->back->data);
}

void* get(List L){ // Returns cursor element of L. Pre: length()>0, index()>=0

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
		if (L->cursor != L->front){
			L->cursor = L->cursor->prev;
			L->index--;
			return;
			// printf("%d", L->cursor->prev->data);
		}
	}

	L->cursor = NULL;
	L->index = -1;
	return;
}

void moveNext(List L){

	if(L->cursor != NULL){
		if (L->cursor != L->back){
			L->cursor = L->cursor->next;
			L->index++;
			return;
			// printf("%d", L->cursor->prev->data);
		}
	}

	L->cursor = NULL;
	L->index = -1;
	return;

	// printf("%d", L->cursor->data);
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, void* data){

    if(L == NULL){
	    printf("List Error: calling prepend() on NULL List reference\n");
	    exit(1);
    }

    Node N = newNode(data);

    if(N == NULL){
    	printf("malloc Error: calling prepend() - failed to allocate storage\n");
		exit(1);
    }

    if( isEmpty(L) ) { 
   		L->front = L->back = N; 
    }else{ 
		L->front->prev = N; 

		N->next = L->front;
		
		L->front = N;

		N->prev = NULL; 
    }

    L->length++;

   	if(L->cursor != NULL)
   		L->index++;

}


// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, void* data){
    if(L == NULL){
		printf("List Error: calling append() on NULL List reference\n");
		exit(1);
    }

    Node N = newNode(data);

    if(N == NULL){
    	printf("malloc Error: calling append() - failed to allocate storage\n");
		exit(1);
    }

    if( isEmpty(L) ) { 
		L->front = L->back = N; 
    }else{ 
		L->back->next = N;
		N->prev = L->back; 

		L->back = N; 
		N->next = NULL;
    }

    L->length++;
} 

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, void* data){

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

	//when cursor is the front node
	if(L->cursor == L->front) {
		prepend(L ,data);
	}else{
		Node N = newNode(data);

		L->cursor->prev->next = N;

	    N->next = L->cursor;
		N->prev = L->cursor->prev;
	    L->cursor->prev = N;

	    L->length++;

		if(L->cursor != NULL)
			L->index++;

	}

}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, void* data){
	
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

    N->next = L->cursor->next;
    L->cursor->next = N;
    N->prev = L->cursor;

    //inserted node after back node
    if(N->next != NULL) {
        N->next->prev = N;
    }
    else {
        L->back = N;
    }

    L->length++;
}

// deleteFront()
// Delete the front element. Pre: length()>0
// Pre: !isEmpty(L)
void deleteFront(List L){ 
    Node N = NULL;

    if( L==NULL ){
	    printf("List Error: calling deleteFront() on NULL List reference\n");
	    exit(1);
    }
    if( isEmpty(L) ){
	    printf("List Error: calling deleteFront() on an empty List\n");
	    exit(1);
    }

    N = L->front;
    if( length(L)>1 ) { 
		L->front = L->front->next; 
		L->front->prev = NULL;
		L->index--;
    }else{ 
		L->front = L->back = NULL;
		L->index = 0;
    }
    L->length--;
    freeNode(&N);
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

	if ( length(L) > 1){
		// printf("%d ", L->back->data);
		L->back = L->back->prev;
		// printf("%d ", L->back->prev->data);
		if (L->back != NULL)
            L->back->next = NULL;
	} else{
		L->front = L->back = NULL;
	}

	L->length--;
    freeNode(&N);
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

	if(L->front == N){
		L->front = N->next;  
	}
	else if(L->back == N){
		L->back = N->prev;
	}
  
    // Node to be deleted when its not in back 
    if (N->next != NULL){
    	N->next->prev = N->prev;
    }
  
    // node to be deleted is not in front
    if (N->prev != NULL){
        N->prev->next = N->next;}  

    L->cursor = NULL;
    L->length--;

	freeNode(&N);
}


//-------------------------------------------------------------------------------
// printList()
// Prints data elements in L on a single line to stdout.

void printList(FILE* out, List L){
    if(L == NULL){
	    printf("List Error: calling printList() on NULL List reference\n");
	    exit(1);
    }

    if(length(L) == 0){
		printf("List Error: calling printList() on NULL List reference\n");
		exit(1);
    }

    Node N = L->front;

    while(N != NULL) {
        printf("%d ", N->data);
        N = N->next;
    }
    // printf("\n");
}

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

	return(nList);
}
