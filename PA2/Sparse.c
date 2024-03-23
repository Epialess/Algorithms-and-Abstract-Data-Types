//-----------------------------------------------------------------------------
// Andy Choi
// achoi15
// pa2
//
// Sparse.c
// Main C file for handling the input and output files
// Client of Matrix ADT
// modified from FileIO.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Matrix.h"


int main(int argc, char* argv[]){

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

	int i, j; // i = row, j = column
	double val;
	fscanf(in, "%d", &i);

	Matrix A = newMatrix(i);
	Matrix B = newMatrix(i);

	fscanf(in, "%d", &i);
	int a = i;

	fscanf(in, "%d", &i);
	int b = i;


	for (int z = 0; z < a; ++z){
		fscanf(in, "%d", &i);
		fscanf(in, "%d", &j);
		fscanf(in, "%lf", &val);
		changeEntry(A, i, j, val);
	 }


	for (int t = 0; t < b; ++t){
		fscanf(in, "%d", &i);
		fscanf(in, "%d", &j);
		fscanf(in, "%lf", &val);
		changeEntry(B, i, j, val);
	 }

	fprintf(out,"A has %d non-zero entries:\n", NNZ(A));
	printMatrix(out, A);

	fprintf(out,"B has %d non-zero entries:\n", NNZ(B));
	printMatrix(out, B);

	fprintf(out,"(1.5)*A =\n");
	printMatrix(out, scalarMult(1.5, A));

	fprintf(out,"A+B =\n");
	printMatrix(out, sum(A, B));

	fprintf(out,"A+A =\n");
	printMatrix(out, sum(A, A));

	fprintf(out,"B-A =\n");
	printMatrix(out, diff(B, A));

	fprintf(out,"A-A =\n");
	printMatrix(out, diff(A, A));

	fprintf(out,"Transpose(A) =\n");
	printMatrix(out, transpose(A));

	fprintf(out,"A*B =\n");
	printMatrix(out, product(A, B));

	fprintf(out,"B*B =\n");
	printMatrix(out, product(B, B));

	fclose(in);
	fclose(out);

	freeMatrix(&A);
	freeMatrix(&B);


	return 0;
}