//-----------------------------------------------------------------------------
// Andy Choi
// achoi15
// pa3
// 
// Arithmetic.c
// C file for BigInteger ADT
// Configured from FileIO.c
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "BigInteger.h"

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

	int a, b;
	fscanf(in, "%d", &a);

	char arr[a];

	fscanf(in, "%s", arr);

	BigInteger A = stringToBigInteger(arr);

	fscanf(in, "%d", &b);

	char bArr[b];

	fscanf(in, "%s", bArr);

	BigInteger B = stringToBigInteger(bArr);


	printBigInteger(out, A);
	printBigInteger(out, B);

	BigInteger C = sum(A, B);
	printBigInteger(out, C);

	BigInteger D = diff(A, B);
	printBigInteger(out, D);

	BigInteger E = diff(A, A);
	printBigInteger(out, E);

	BigInteger Z = sum(A, A); 
	add(Z, A, Z); // 3A

	BigInteger X = sum(B, B); // 2B

	BigInteger G = diff(Z, X); // 3A - 2B
	printBigInteger(out, G);

	BigInteger H = prod(A, B);
	printBigInteger(out, H);

	BigInteger I = prod(A, A);
	printBigInteger(out, I);

	BigInteger J = prod(B, B); //B^2
	printBigInteger(out, J);

	BigInteger K = prod(X, X); //2B * 2B = 4B^2

	BigInteger L = prod(Z, Z); // 3A * 3A = 9A^2
	BigInteger M = prod(I, L); // A^2 * 9A^2 = 9A^4

	BigInteger N = prod(K, K); // 4B^2 * 4B^2 = 16B^4
	BigInteger P = prod(B, N); // 16B^5

	BigInteger Q = sum(M, P); //9A^4 + 16B^5
	printBigInteger(out, Q);

	fclose(in);
	fclose(out);

	freeBigInteger(&A);
	freeBigInteger(&B);
	freeBigInteger(&C);
	freeBigInteger(&D);
	freeBigInteger(&E);
	freeBigInteger(&G);
	freeBigInteger(&H);
	freeBigInteger(&I);
	freeBigInteger(&J);
	freeBigInteger(&K);
	freeBigInteger(&L);
	freeBigInteger(&N);
	freeBigInteger(&M);
	freeBigInteger(&P);
	freeBigInteger(&Q);
	freeBigInteger(&Z);
	freeBigInteger(&X);




	return 0;
}