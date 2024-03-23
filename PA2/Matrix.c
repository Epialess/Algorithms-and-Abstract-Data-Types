//-----------------------------------------------------------------------------
// Andy Choi
// achoi15
// pa2
//
// Matrix.c
// C file for Matrix ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Matrix.h"
#include "List.h"


//-----------------------------------------------------------------------------
// Structures
//-----------------------------------------------------------------------------

// private EntryObj type
typedef struct EntryObj{
	int column;
	double value;
} EntryObj;

// private Entry type
typedef EntryObj* Entry;

// private MatrixObj type
typedef struct MatrixObj{
	int sizeM; // size of matrix n
	int nnz; // number of non-zeros
	List* L; // array of list holding the row value 

} MatrixObj;

//-----------------------------------------------------------------------------
// Constructors-Destructors
//-----------------------------------------------------------------------------


// newEntry()
// Returns reference to new Entry object. Initializes column and value fields.
// Private.
Entry newEntry(int col, double val){
	Entry E = malloc(sizeof(EntryObj));
	E->column = col;
	E->value = val;
	return(E);
}

// freeEntry()
// Frees heap memory associated with *pE, sets *pE to NULL.
void freeEntry(Entry* pE){
	if( pE != NULL && *pE != NULL ){
		free(*pE);
		*pE = NULL;
   }
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
	if (n < 1){
		printf("Matrix Error: calling newMatrix() with a negative or 0 size.\n");
		exit(1);
	}

	Matrix M = malloc(sizeof(MatrixObj));
	M->L = calloc(n, sizeof(List)); // allocates mem for list 
	M->sizeM = n;
	M->nnz = 0;

	for(int i = 0; i < n; i++){
		M->L[i] = newList();
	}

	return(M);
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
	int dim = (*pM)->sizeM;
	
	if(pM != NULL && *pM != NULL){ 

		for(int i = 0; i < dim; i++){ // iterates list array

			while( length((*pM)->L[i]) != 0){ // while length of list != 0

				moveFront( (*pM)->L[i] );
				Entry E = (Entry)get((*pM)->L[i]);

				freeEntry(&E);
				deleteFront((*pM)->L[i]);

			}
			clear((*pM)->L[i]);
			freeList(&(*pM)->L[i]);
		}
   }
   free(*pM);
   *pM = NULL;

}

//-----------------------------------------------------------------------------
// Access functions
//-----------------------------------------------------------------------------

// size()
// Return the size of square Matrix M.
int size(Matrix M){

	if( M == NULL ){
		printf("Matrix Error: calling size() on NULL Matrix reference\n");
		exit(1);
	}

	return(M->sizeM);
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){

	if( M == NULL ){
		printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
		exit(1);
	}

	return(M->nnz);
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
	if(size(A) != size(B)){ // compares sizes
		return 0;
	}

	int szA = size(A);

	for(int i = 0; i < szA; i++ ){

		if(length(A->L[i]) != length(B->L[i])) // compares lengths of arrays
			return 0;

		while(index(A->L[i]) >= 0){
			for (int j = 0; j < szA; j++){  //iterates each list entry
				Entry E = (Entry)get(A->L[j]);
				Entry E2 = (Entry)get(B->L[j]);
				
				if( E->value != E2->value ){ // compares entry values
					return 0;
				}
			}
		}
 
	}
	return 1;
}

//-----------------------------------------------------------------------------
// Manipulation procedures
//-----------------------------------------------------------------------------

// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M){

	int sz = size(M);

	for(int i = 0; i < sz; i++){ // iterates list array

		while(length(M->L[i]) != 0){ // while length of list is not 0
			moveFront(M->L[i]);
			Entry E = (Entry)get(M->L[i]);
			// free its entry and delete entry
			freeEntry(&E);
			M->nnz--;
			deleteFront(M->L[i]);
		}
	}
	return;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){

	if(M == NULL) {
		printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
		exit(1);
	}

	if((i > size(M)) || (i < 1) ){
		printf("Matrix error: changeEntry() ith row is not in the range of 1 to matrix size.\n");
		exit(1);
	}

	if((j > size(M)) || (j < 1) ){
		printf("Matrix error: changeEntry() jth row is not in the range of 1 to matrix size.\n");
		exit(1);
	}


	if( isEmpty(M->L[i-1]) && x != 0){ // base case when matrix is empty and x != 0
		append(M->L[i-1], newEntry(j, x));
		M->nnz++;
		return;
	}

	moveFront(M->L[i-1]); // moves cursor to front of i list

	while(index(M->L[i-1]) >= 0){

		Entry E = (Entry)get(M->L[i-1]); // current entry

		if(E->column == j){ // if jth col is in row

			if(x == 0.0){ //case 2: delete entry obj
				freeEntry(&E);
				delete(M->L[i-1]);
				M->nnz--;
				return;
			}
			if(x != 0.0 ){ //case 4: overwrite entry
				E->value = x;
				return;
			}				
		}
		else if(E->column > j){ // // if greater than curr column, insert before 
			if(x == 0.0 ) //case 1: do nothing
				return;

			insertBefore(M->L[i-1], newEntry(j, x));  //case 3: insert new entry    
			M->nnz++;
			return;
		}
		moveNext(M->L[i-1]);
	}

	// when entries dont match rest of columns
	append(M->L[i-1], newEntry(j,x)); // creates new entry and append
	M->nnz++;
	return;
}

//-----------------------------------------------------------------------------
// Matrix Arithmetic operations
//-----------------------------------------------------------------------------

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){

	int sz = size(A);
	Matrix cM = newMatrix(sz);

	for(int i = 0; i < sz; i++){
		if(!isEmpty(A->L[i])){ // checks if list is not empty
			moveFront(A->L[i]);
			while(index(A->L[i]) >= 0){ //while cursor is not undefined in A
				Entry E = (Entry)get(A->L[i]); // current entry of A
				append(cM->L[i], newEntry(E->column, E->value)); // append to copy matrix
				cM->nnz++;
				moveNext(A->L[i]);
			}
		}
	}
	return(cM);
}


// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
	int sz = size(A);
	Matrix tM = newMatrix(sz);

	for(int i = 0; i < sz; i++){
		if(!isEmpty(A->L[i])){ // checks if list is not empty
			moveFront(A->L[i]);
			while(index(A->L[i]) >= 0){ //while cursor is not undefined in A
				Entry E = (Entry)get(A->L[i]); // current entry of A
				changeEntry(tM, E->column, i + 1 , E->value); // changes entry by switching i and j
				moveNext(A->L[i]);
			}

		}
	}
	return(tM);
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){

	int sz = size(A);

	Matrix scalM = newMatrix(sz);

	for(int i = 0; i < sz; i++){
		if(!isEmpty(A->L[i])){ // checks if list is not empty
			moveFront(A->L[i]); 
			while(index(A->L[i]) >= 0){
				Entry E = (Entry)get(A->L[i]); // current entry of A
				append(scalM->L[i], newEntry(E->column, E->value * x)); // append to scalar matrix
				scalM->nnz++;
				moveNext(A->L[i]);
			}
		}
	}
	return(scalM);
}


// sumList()
// Helper function for sum()
// Returns the number of nnz in two lists P and Q
int sumList(List P, List Q, List S){
	int nnz = 0; // non-zeros in list

	if(!isEmpty(Q) || !isEmpty(P)){ // checks if arrays are empty

		moveFront(P);
		moveFront(Q);

		while(index(Q) >= 0 || index(P) >= 0){ //stops when cursor is undefined
			
			if(index(Q) == -1 ){ // case if Q cursor is undefined append P entry 
				Entry eP = get(P);

				append(S, newEntry(eP->column, eP->value));
				moveNext(P);
				nnz++;
			}
			else if(index(P) == -1 ){// case if P cursor is undefined append Q entry
				Entry eQ = get(Q);

				append(S, newEntry(eQ->column, eQ->value));
				moveNext(Q);
				nnz++;
			}else{

				Entry eP = get(P);
				Entry eQ = get(Q);


				if(eP->column == eQ->column){ // case if similar column is found
					
					if(P == Q){ // case if P and Q are identical
						append(S, newEntry(eP->column, eP->value * 2 )); // times 2 and append to S
						nnz++;
						moveNext(Q); // moves Q next cursor
	
					} else if(eP->value + eQ->value != 0.0){ // checks if adding result returns 0
						append(S, newEntry(eP->column, eP->value + eQ->value)); // add values and append to S
						nnz++;
						moveNext(Q); // moves Q next cursor
						moveNext(P); // moves P next cursor
					}
					else{
						moveNext(Q); // moves Q next cursor
						moveNext(P); // moves P next cursor
					}

				}


				if(eP->column < eQ->column){ // if Q entry is greater than P entry
					append(S, newEntry(eP->column, eP->value)); // append to S
					nnz++;
					moveNext(P); // move P next
				}

				if(eP->column > eQ->column){ // if column P is greater than Q
					append(S, newEntry(eQ->column, eQ->value)); // append to S
					nnz++;
					moveNext(Q); // move Q next
				}
			}
		}
	}

	return(nnz);
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){

	if(size(A) != size(B)){ // compares sizes
		printf("Matrix Error: calling sum() on different sizes of matrices.\n");
		exit(1);
	}

	int sz = size(A);
	Matrix sumM = newMatrix(sz);

	for(int i = 0; i < sz; i++) // iterates sumM list to input matrix entries
		sumM->nnz += sumList(A->L[i], B->L[i], sumM->L[i]);	

   return(sumM);
}


// diffList()
// Helper function for diff()
// Returns the number of nnz in two lists P and Q
int diffList(List P, List Q, List S){
	int nnz = 0; // non-zeros in list

	if(!isEmpty(Q) || !isEmpty(P)){ // checks if arrays are empty

		moveFront(P);
		moveFront(Q);

		while(index(Q) >= 0 || index(P) >= 0){ //stops when cursor is undefined
			
			if(index(Q) == -1 ){ // case: if Q cursor is undefined append P entry 
				Entry eP = get(P);

				append(S, newEntry(eP->column, eP->value));
				moveNext(P);
				nnz++;
			}
			else if(index(P) == -1 ){// case: if P cursor is undefined append Q entry
				Entry eQ = get(Q);

				append(S, newEntry(eQ->column, 0 - eQ->value)); // append neq q val to S
				moveNext(Q);
				nnz++;
			}else{

				Entry eP = get(P);
				Entry eQ = get(Q);

				if(eP->column == eQ->column){ // case: if similar column is found

					if(P == Q){ // case if P and Q are identical, empty list
						moveNext(Q); // moves Q next cursor
					}else if(eP->value - eQ->value != 0.0){ // first check if subtracting results in != 0
						append(S, newEntry(eP->column, eP->value - eQ->value)); // subtract values and append to S
						nnz++;
						moveNext(Q); // moves Q next cursor
						moveNext(P); // moves P next cursor
					}
					else{
						moveNext(Q); // moves Q next cursor
						moveNext(P); // moves P next cursor
					}

				}

				if(eP->column < eQ->column){ // if Q entry is greater than P entry
					append(S, newEntry(eP->column, eP->value)); // append to S
					nnz++;
					moveNext(P); // move P next
				}

				if(eP->column > eQ->column){ // if column P is greater than Q
					append(S, newEntry(eQ->column, 0 - eQ->value)); // append neg q val to S
					nnz++;
					moveNext(Q); // move Q next
				}
			}
		}
	}

	return(nnz);
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
	if(size(A) != size(B)){ // compares sizes
		printf("Matrix Error: calling diff() on different sizes of matrices.\n");
		exit(1);
	}

	int sz = size(A);
	Matrix diffM = newMatrix(sz);

	for(int i = 0; i < sz; i++) // iterates diffM list to input matrix entries
		diffM->nnz += diffList(A->L[i], B->L[i], diffM->L[i]);	

   return(diffM);
}


// vectorDot()
// Helper function for product()
// Returns the sum of two lists P and Q
double vectorDot(List P, List Q){
	double sum = 0.0;

	if(!isEmpty(Q) && !isEmpty(P)){
		moveFront(P);
		moveFront(Q);

		while(index(Q) >= 0 || index(P) >= 0){ //stops when a cursor is undefined
			
			if(index(Q) == -1 ){ // case: if Q cursor is undefined do nothing
				moveNext(P);
			}
			else if(index(P) == -1 ){// case: if P cursor is undefined do nothing
				moveNext(Q);
			}else{

				Entry eP = get(P);
				Entry eQ = get(Q);

				if(eP->column == eQ->column){ // case if similar column is found
					sum += eP->value * eQ->value;
					moveNext(Q); // moves Q next cursor
					moveNext(P); // moves P next cursor
				}

				if(eP->column < eQ->column){ // if column Q is greater than P
					moveNext(P); // move P next
				}

				if(eP->column > eQ->column){ // if column P is greater than Q
					moveNext(Q); // move Q next
				}
			}
		}
	}
	return(sum);
}


// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
	if(size(A) != size(B)){ // compares sizes
		printf("Matrix Error: calling product() on different sizes of matrices.\n");
		exit(1);
	}

	int sz = size(A);

	Matrix prodM = newMatrix(sz);
	Matrix transM = transpose(B);

	for(int i = 0; i < sz; i++){
		if(!isEmpty(A->L[i])){ // checks if list is not empty

			for (int j = 0; j < sz; j++){
				double vDot = vectorDot(A->L[i], transM->L[j]); //every row of A to every row transpose B

				if( vDot != 0.0 ){
					append(prodM->L[i], newEntry(j+1, vDot));
					prodM->nnz++;
				}
			}
		}
	}
	return(prodM);
}



// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){

	int sz = size(M);
	for(int i = 0; i < sz; i++){ // iterate list array
		if(!isEmpty(M->L[i])){ // checks if list is not empty
			moveFront(M->L[i]); 
			fprintf(out, "%d: ", i+1);
			while(index(M->L[i]) >= 0){ //while cursor is not undefined
				Entry E = (Entry)get(M->L[i]);
				fprintf(out ,"(%d, %.1f) ", E->column, E->value);
				moveNext(M->L[i]);
			}
			fprintf(out, "\n");
		}
	}
	fprintf(out, "\n");
	return;
}

