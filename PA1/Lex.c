//-----------------------------------------------------------------------------
// Andy Choi
// achoi15
// pa1
//
// Lex.c
// C file for rearrangement in lexicographic order
// modified from FileIO.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"List.h"


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

	int const MAX_LEN = 100;
	int const MAX_LINE = 50;
	int count = 0;
	char s[MAX_LINE][MAX_LEN];

   /* read each line of input file, then count */
   while( fgets(s[count], MAX_LEN, in) != NULL)  {
	// printf("read %s", s[count]);
	count++;
   }

   // printf("%d \n",count );

	List L = newList();

	append(L, 0);
	int x = index(L);

	for(int i = x + 1; i < count; ++i) { // i = 1,2,3
		// printList(L);
		// printf("i:%d\n",i);
		moveFront(L);
		// printf("index before:%d , data before:%d \n", index(L), get(L) );
		x = index(L);

		while (x != -1){
			//printf("x:%d \n", x);
			// printf("index:%d \n",index(L));
			// printf("comparing %d with %d \n", index(L),i);
			if( strcmp(s[get(L)], s[i]) > 0) { // if str[0] comes after str[1] = true
				insertBefore(L, i);
				x = -1;
			}
			else if( index(L) + 1== length(L) ){
				append(L, i);
				x = -1;
			}
			// printf("length:%d\n",length(L));
			// printf("index: %d\n",index(L) );

			moveNext(L);
			
		}
	}
	// printList(stdout, L);
	moveFront(L);
	while(index(L) >= 0) {
		fprintf( out, "%s", s[get(L)] ); //outputs cursor element in file
		moveNext(L);
	}

	/* close files */
	fclose(in);
	fclose(out);

	freeList(&L);

	return 0;
}