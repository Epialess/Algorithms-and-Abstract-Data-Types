//-----------------------------------------------------------------------------
// Andy Choi
// achoi15
// pa3
//
// ListTest.c
// C Test file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){

   List A = newList();
   // List B = *p;
   append(A, 1);
   append(A, 2);
   moveFront(A);
   printList(A); 

   printf("index: %d\n",index(A));

   printf("\n");

   delete(A);

   printList(A); 
   printf("\n");

   append(A, 3);
   append(A, 5);
   moveFront(A);
   insertAfter(A, 12);
   delete(A);

   printf("l: %d\n",length(A));

   if (length(A) != 3) return 1;





   // append(A, 5);
   // prepend(A, 7);
   // append(A, 2);
   // moveBack(A);
   // printf("index1 %d\n",index(A));

   // insertAfter(A, 43);
   // printList(A); 

   // deleteBack(A);
   // printList(A); 
   // printf("\n");
   // printf("back1 %ld\n",back(A));
   // printf("\n");



   // delete(A);
   // printList(A); 
   // printf("\n");
   // printf("back %ld\n",back(A));

   // if (back(A) != 5) return 1;


   // prepend(A, 5);
   // prepend(A, 65);
   // prepend(A, 43);
   // prepend(A, 2);
   // prepend(A, 8);
   // prepend(A, 1);
   // moveFront(A);
   //  printf("index1 %d\n",index(A));

   // deleteFront(A);
   //  printf("index %d\n",index(A));

   // if (index(A) != -1) return 1;

   // moveBack(A);
   //  printf("index2 %d\n",index(A));

   // deleteFront(A);
   //  printf("index end %d\n",index(A));

   // if (index(A) != 3) return 2;
    
   // List A = newList();
   // List B = newList();
   // List C = NULL;
   // long i;

   // for(i=1; i<=20; i++){
   //    append(A,i);
   //    prepend(B,i);
   // }


   // printList(A); 
   // printf("\n");
   // // printList(B); 
   // printf("\n");

   // moveFront(A);

   // set(A, 1111);
   // printList(A); 

   // for(moveFront(A); index(A)>=0; moveNext(A)){
   //    printf("%ld ", get(A));
   // }
   // printf("\n");
   // for(moveBack(B); index(B)>=0; movePrev(B)){
   //    printf("%ld ", get(B));
   // }
   // printf("\n");

   // moveFront(A);
   // for(i=0; i<5; i++) moveNext(A); // at index 5
   // insertBefore(A, -1);            // at index 6
   // for(i=0; i<9; i++) moveNext(A); // at index 15
   // insertAfter(A, -2);
   // for(i=0; i<5; i++) movePrev(A); // at index 10
   // delete(A);
   // printList(A);
   // printf("\n");
   // printf("%d\n", length(A));
   // clear(A);
   // printf("%d\n", length(A));

   // freeList(&A);
   // freeList(&B);
   // freeList(&C);

   return(0);
}

/*
Output of this program:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20


1111 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1111 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1111 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20

21
0
*/