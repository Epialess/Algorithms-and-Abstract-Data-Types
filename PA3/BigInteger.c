//-----------------------------------------------------------------------------
// Andy Choi
// achoi15
// pa3
// 
// BigInteger.h
// C file for BigInteger ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "List.h"
#include "BigInteger.h"


const int POWER = 9;

int powTen(int pow){
	static const int values[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
	return values[pow];
}

// structs --------------------------------------------------------------------

// private BigIntegerObj type
typedef struct BigIntegerObj{
	int sign;
	List L;

} BigIntegerObj;

// private BigInteger type
typedef BigIntegerObj* BigInteger;

// Constructors-Destructors ---------------------------------------------------
// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(){
	BigInteger B = malloc(sizeof(BigIntegerObj));
	B->sign = 0;
	B->L = newList();

	return(B);
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN){

	if( pN != NULL && *pN != NULL ){
    	freeList(&(*pN)->L);

		free(*pN);
		*pN = NULL;
    }
}

// Access functions -----------------------------------------------------------
// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N){
	if(N == NULL){
		printf("BigInteger Error: calling sign() on NULL BigInteger reference\n");
		exit(1);
	}

	return(N->sign);
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){

	moveFront(A->L);
	moveFront(B->L);

	if(equals(A, B)){
		return 0;
	}

	// printf("signA %d\n",sign(A));
	// printf("signB %d\n",sign(B));

	if(sign(A) < sign(B)){ // if A is - and B is +
		return -1;
	}

	if(sign(A) > sign(B)){// if A is + and B is - 
		return 1;
	}
	// printf("signA %d\n",sign(A));
	// printf("signB %d\n",sign(B));

	if(length(A->L) < length(B->L)){
		return -1;
	}
	else if(length(A->L) > length(B->L)){
		return 1;
	}


	if(sign(A) == -1 && sign(B) == -1){ //-A -B same index
		while(index(A->L) >= 0 && index(B->L) >= 0){
			if(get(A->L) > get(B->L)){
				return -1;
			}
			else if(get(A->L) < get(B->L)) return 1;
			moveNext(A->L);
			moveNext(B->L);
		}
	}

	if(sign(A) == 1 && sign(B) == 1){ //A B same index

		while(index(A->L) >= 0 && index(B->L) >= 0){
			if(get(A->L) > get(B->L)){
				return 1;
			}
			else if(get(A->L) < get(B->L))
				return -1;
			moveNext(A->L);
			moveNext(B->L);
		}
	}
	return 0;
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){

	int len = length(A->L);

	if(len != length(B->L)){ // compares length of lists
		return 0;
	}

	if(sign(A) != sign(B)) // compares sign 
		return 0;

	if(sign(A) == 0 && sign(B) == 0){// if A and B are both in the zero state

		return 1;

	}

	moveFront(A->L);
	moveFront(B->L);



	while(index(A->L) != -1 || index(B->L) != -1){
		if( get(A->L) != get(B->L)){
			return 0;
		}
		moveNext(A->L);
		moveNext(B->L);
		
	}


	return 1;
}

// Manipulation procedures ----------------------------------------------------
// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){

	if(N == NULL){
		printf("BigInteger Error: calling makeZero() on NULL BigInteger reference\n");
		exit(1);
	}

	moveBack(N->L);

	while(!isEmpty(N->L)){
		deleteBack(N->L);
	}

	N->sign = 0;

	return;
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N){
	if(sign(N) == 1)
		N->sign = -1;
	else if(sign(N) == -1)
		N->sign = 1;

	return;
}

// BigInteger Arithmetic operations -----------------------------------------------
// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9} and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s){

	if(s[0] == '\0'){
	    printf("BigInteger Error: calling stringToBigInteger() on empty char array.\n");
	    exit(1);
	}

	BigInteger N = newBigInteger();

	int temp = 0; // keeps track if there is a sign or not in array

	if(s[0] == '+'){
		N->sign = 1;
		temp++;
	}
	else if(s[0] == '-'){

		N->sign = -1;
		temp++;
	}
	else
		N->sign = 1;


	int len = strlen(s) - 1;

	long num = 0;
	int count = 0;

	for(int i = len; i >= 0; --i){

		if(temp == 1){ // if s[0] contains + or -, ignore s[0]
			if(i != 0){
			    num += (s[i] - '0') * powTen(count);
				count++;

				if((count % POWER == 0)){ // add to list and reset iteration
					prepend(N->L, num);
					num = 0;
					count = 0;
				}
			}

			if(i == 0 && num != 0){ // prepend last long num
				prepend(N->L, num);
			}
		}
		else{
		    num += (s[i] - '0') * powTen(count);
			count++;
			// printf("num: %ld\n", num);

			if((count % POWER == 0)){ // add to list and reset iteration
				prepend(N->L, num);
				num = 0;
				count = 0;
			}

			if(i == 0 && num != 0){ // prepend last long num
				prepend(N->L, num);
			}
		}

	}


	moveFront(N->L);
	while(get(N->L) == 0 && !isEmpty(N->L)){ // deletes leading zero
		deleteFront(N->L);
		moveFront(N->L);
	}

	if(isEmpty(N->L)){ //sets sign to zero if in zero state
		N->sign = 0;
	}

	return(N);
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){

	if(N == NULL){
		printf("BigInteger Error: calling copy() on NULL BigInteger reference\n");
		exit(1);
	}

	BigInteger C = malloc(sizeof(BigIntegerObj));

	C->L = copyList(N->L);

	C->sign = N->sign;

	return(C);
}

// normalize()
// Helper function to normalize N 
void normalize(BigInteger N){
	moveBack(N->L);
	int carry = 0;


	while(index(N->L) != -1){
		long temp = get(N->L);

		if(carry != 0){ // add
			set(N->L, temp + carry);
			temp += carry;
			carry = 0;
		}

		if(temp < 0){ // subtract
			set(N->L, temp + powTen(POWER));
			carry = -1;
		}

		if(temp >= powTen(POWER)){ // multiply
			set(N->L, temp % powTen(POWER));
			carry = temp / powTen(POWER);
			movePrev(N->L);
		}else{
			movePrev(N->L);
		}
	}

	if(carry != 0) 
		prepend(N->L, carry);

	//delete leading zeroes
	moveFront(N->L);
	while(!isEmpty(N->L) && get(N->L) == 0){
		deleteFront(N->L);
		moveFront(N->L);
	}

	if(isEmpty(N->L)){ //sets sign to zero if in zero state
		N->sign = 0;
	}
	
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){

	if(S == NULL){
		printf("BigInteger Error: calling add() on S NULL BigInteger reference\n");
		exit(1);
	}
	if(A == NULL){
		printf("BigInteger Error: calling add() on A NULL BigInteger reference\n");
		exit(2);
	}

	if(B == NULL){
		printf("BigInteger Error: calling add() on B NULL BigInteger reference\n");
		exit(3);
	}

	List sL = S->L;

	BigInteger C = copy(A);
	BigInteger Z = copy(B);

	List aL = C->L;
	List bL = Z->L;


	makeZero(S);
	// printf("SignA: %d\n", sign(A));
	// printf("SignB: %d\n", sign(B));

	if(sign(C) > 0 && sign(Z) < 0){
		negate(Z);
		subtract(S, C, Z);
		freeBigInteger(&Z);
		freeBigInteger(&C);
		return;
	}
	else if(sign(C) < 0 && sign(Z) > 0){
		negate(C);
		subtract(S, Z, C);
		freeBigInteger(&Z);
		freeBigInteger(&C);
		return;
	}

	//case: A && B with the same sign: 
	if(sign(C) == sign(Z) || sign(C) == 0 || sign(Z) == 0 ){ 
		moveBack(aL);
		moveBack(bL);

		while(index(aL) >= 0 || index(bL) >= 0){ 

			if(index(bL) == -1){ // when bL reaches null, prepend rest of aL
				prepend(sL, get(aL));
				movePrev(aL);
			}
			else if(index(aL) == -1){ // when aL reaches null, prepend rest of bL
				prepend(sL, get(bL));
				movePrev(bL);
			}else{
				prepend(sL, get(aL) + get(bL));
				movePrev(aL); 
				movePrev(bL);
			}
		}
		// sets sign accoridngly
		if(sign(C) + sign(Z) > 0)
			S->sign = 1;
		else if (sign(C) + sign(Z) < 0)
			S->sign = -1;
		else
			S->sign = 0;

		normalize(S);
	}

	freeBigInteger(&Z);
	freeBigInteger(&C);

	return;
}
// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
	BigInteger S = newBigInteger();
	add(S, A, B);
	return S;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B){
	if(D == NULL){
		printf("BigInteger Error: calling subtract() on D NULL BigInteger reference\n");
		exit(1);
	}
	if(A == NULL){
		printf("BigInteger Error: calling subtract() on A NULL BigInteger reference\n");
		exit(2);
	}

	if(B == NULL){
		printf("BigInteger Error: calling subtract() on B NULL BigInteger reference\n");
		exit(3);
	}

	List dL = D->L;

	BigInteger C = copy(A);
	BigInteger Z = copy(B);

	// compare(A,B);
	makeZero(D);

	// if A - and B +
	if(sign(C) < 0 && sign(Z) > 0){
		negate(Z);
		add(D, C, Z);
		freeBigInteger(&Z);
		freeBigInteger(&C);

		return;
	}
	// if A + and B -
	else if(sign(C) > 0 && sign(Z) < 0){
		negate(Z);
		add(D, C, Z);
		freeBigInteger(&Z);
		freeBigInteger(&C);
		return;
	}

	int flip = compare(C,Z);
	// printf("flip: %d\n", flip);

	if(flip == -1){
		// printf("flip\n");
		BigInteger Y = C;
		C = Z;
		Z = Y;
	}

	// printf("C:\n");
	// printBigInteger(stdout, C);
	// printf("Z\n");
	// printBigInteger(stdout, Z);

	List aL = C->L;
	List bL = Z->L;

	//case: A && B with the same sign: 
	if(sign(C) == sign(Z) || sign(C) == 0 || sign(Z) == 0 ){ 
		moveBack(aL);
		moveBack(bL);

		while(index(aL) >= 0 || index(bL) >= 0){ 

			if(index(bL) == -1){ // when bL reaches null, prepend rest of aL
				prepend(dL, get(aL));
				movePrev(aL);
			}
			else if(index(aL) == -1){ // when aL reaches null, prepend rest of bL
				prepend(dL, 0 - get(bL));
				movePrev(bL);
			}else{
				long temp = get(aL) - get(bL);

				prepend(dL, temp);

				// printf("getdl: %ld\n", get(dL));
				// printf("temp: %ld\n", temp);

				// printf("getbl: %ld\n", get(bL));
				// printf("getal: %ld\n", get(aL));

				movePrev(aL); 
				movePrev(bL);
			}

		}
			// printf("get(dL): %ld\n", front(dL));

		//sets sign accordingly
		if(front(dL) < 0 ){ //if +
			moveFront(dL);
			// printf("get(dL): %ld\n", get(dL));

			set(dL, -1* get(dL));
			// printf("get2(dL): %ld\n", get(dL));

		}
	
		D->sign = 1;
		

		normalize(D);
	}

	if(flip == -1)
		negate(D);

	freeBigInteger(&C);
	freeBigInteger(&Z);


	return;
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B){
	BigInteger D = newBigInteger();
	subtract(D, A, B);

	return D;	
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){

	if(P == NULL){
		printf("BigInteger Error: calling multiply() on P NULL BigInteger reference\n");
		exit(1);
	}
	if(A == NULL){
		printf("BigInteger Error: calling multiply() on A NULL BigInteger reference\n");
		exit(2);
	}

	if(B == NULL){
		printf("BigInteger Error: calling multiply() on B NULL BigInteger reference\n");
		exit(3);
	}

	if(sign(A) == 0 || sign(B) == 0){
		makeZero(P);
		return;
	}

	BigInteger X = copy(A);
	BigInteger Y = copy(B);

	List xL = X->L;
	List yL = Y->L;


	makeZero(P);
	
	long num = 0;
	int count = 0;

	BigInteger T = newBigInteger();

	List tL = T->L;

	moveBack(xL);
	while(index(xL) >= 0){
		moveBack(yL);

		makeZero(T);
		T->sign = 1;

		for(int i = 0; i < count; ++i){ // prepends 0 for multiplying
			prepend(tL, 0);
		}
		while(index(yL) >= 0){
			num = get(xL) * get(yL); // 
			prepend(tL, num);
			movePrev(yL);
		}
		count++;
		// printf("T:");

		// printBigInteger(stdout, T);
		normalize(T);
		
		// printf("T2:");

		// printBigInteger(stdout, T);

		add(P, P, T); //add each column of T to P

		// printf("notNormP:");

		// printBigInteger(stdout, P);

		movePrev(xL);
	}

	normalize(P);

	// printf("normP:");
	// printBigInteger(stdout, P);

	if(sign(X) != sign(Y))
		P->sign = -1; 

	freeBigInteger(&X);
	freeBigInteger(&Y);
	freeBigInteger(&T);
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){
	BigInteger P = newBigInteger();
	multiply(P, A, B);

	return P;
}

// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
// void printBigInteger(FILE* out, BigInteger N);

void printBigInteger(FILE* out, BigInteger N){
	if(N == NULL){
	    printf("BigInteger Error: calling printBigInteger() on NULL List reference\n");
	    exit(1);
    }

    if(sign(N) == 0){
    	fprintf(out, "0\n\n");
    	return;
    }

    moveFront(N->L);
    if(sign(N) == -1){
    	fprintf(out, "-");
    }

    fprintf(out, "%ld", get(N->L));
    moveNext(N->L);
    // printf("Index: %d\n", index(N->L) );

    while(index(N->L) >= 0){
    	fprintf(out, "%.*ld",POWER, get(N->L));
       	moveNext(N->L);
    }
    fprintf(out,"\n\n");
}


