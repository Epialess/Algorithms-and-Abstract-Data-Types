//-----------------------------------------------------------------------------
// Andy Choi
// achoi15
// pa3
// 
// BigIntegerTest.c
// C Test file for BigInteger ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"
	 
int main() {


	BigInteger pA = stringToBigInteger("-111122223333");
	printBigInteger(stdout, pA);

    BigInteger pB = stringToBigInteger("-112122223333");
	printBigInteger(stdout, pB);

	BigInteger C = newBigInteger();
    C = diff(pA, pB);

    printBigInteger(stdout, C);

    // printf("sign: %d\n", sign(C));

    freeBigInteger(&pA);
    freeBigInteger(&pB);
    freeBigInteger(&C);


// 	printf("s0: ");
// 	BigInteger s0 = stringToBigInteger("-12345");
// 	printBigInteger(stdout, s0);
	
// 	printf("s1: ");
// 	BigInteger s1 = stringToBigInteger("+12345");
// 	printBigInteger(stdout, s1);
	
// 	printf("s2: ");
// 	BigInteger s2 = stringToBigInteger("-0023402");
// 	printBigInteger(stdout, s2);
	
// 	printf("s3: ");
// 	BigInteger s3 = stringToBigInteger("89325323");
// 	printBigInteger(stdout, s3);
	
// 	printf("s4: ");
// 	BigInteger s4 = stringToBigInteger("+532222660100");
// 	printBigInteger(stdout, s4);
	
// 	printf("s5: ");
// 	BigInteger s5 = stringToBigInteger("-432532243");
// 	printBigInteger(stdout, s5);
	
// 	printf("s6: ");
// 	BigInteger s6 = stringToBigInteger("+63222222223120");
// 	printBigInteger(stdout, s6);
	
// 	printf("s7: ");
// 	BigInteger s7 = stringToBigInteger("-000000000000000000000000004");
// 	printBigInteger(stdout, s7);
	
// 	printf("s8: ");
// 	BigInteger s8 = stringToBigInteger("00000000000000000000000001");
// 	printBigInteger(stdout, s8);
	
// //--------------------------------------------------------------------------
// //add
// 	printf("\ns0: ");
// 	printBigInteger(stdout, s0);
// 	printf("s0 = s1 + s0\n");
// 	add(s0, s1, s0);
// 	printf("s0: ");
// 	printBigInteger(stdout, s0);
	
// 	printf("\ns2: ");
// 	printBigInteger(stdout, s2);
// 	printf("s2 = s2 + s1\n");
// 	add(s2, s2, s1);
// 	printf("s2: ");
// 	printBigInteger(stdout, s2);
	
// 	printf("\ns1: ");
// 	printBigInteger(stdout, s1);
// 	printf("s1 = s1 + s1\n");
// 	add(s1, s1, s1);
// 	printf("s1: ");
// 	printBigInteger(stdout, s1);
	
// 	printf("\ns7: ");
// 	printBigInteger(stdout, s7);
// 	printf("s7 = s1 + s1\n");
// 	add(s7, s1, s1);
// 	printf("s7: ");
// 	printBigInteger(stdout, s7);
// //--------------------------------------------------------------------------
// //subtract
// 	printf("\ns7: ");
// 	printBigInteger(stdout, s7);
// 	printf("s7 = s5 - s7\n");
// 	subtract(s7, s5, s7);
// 	printf("s7: ");
// 	printBigInteger(stdout, s7);
	
// 	printf("\ns7: ");
// 	printBigInteger(stdout, s7);
// 	printf("s7 = s4 - s4\n");
// 	subtract(s7, s4, s4);
// 	printf("s7: ");
// 	printBigInteger(stdout, s7);
	
// 	printf("\ns4: ");
// 	printBigInteger(stdout, s4);
// 	printf("s4 = s4 - s1\n");
// 	subtract(s4, s4, s1);
// 	printf("s4: ");
// 	printBigInteger(stdout, s4);
	
// 	printf("\ns3: ");
// 	printBigInteger(stdout, s3);
// 	printf("s3 = s3 - s3\n");
// 	subtract(s3, s3, s3);
// 	printf("s3: ");
// 	printBigInteger(stdout, s3);
// //--------------------------------------------------------------------------
// 	printf("\ns1: ");
// 	printBigInteger(stdout, s1);
// 	printf("s1 = s0 * s1\n");
// 	multiply(s1, s0, s1);
// 	printf("s1: ");
// 	printBigInteger(stdout, s1);
	
// 	printf("\ns5: ");
// 	printBigInteger(stdout, s5);
// 	printf("s5 = s5 * s6\n");
// 	multiply(s5, s5, s6);
// 	printf("s5: ");
// 	printBigInteger(stdout, s5);
	
// 	printf("\ns8: ");
// 	printBigInteger(stdout, s8);
// 	printf("s8 = s8 * s8\n");
// 	multiply(s8, s8, s8);
// 	printf("s8: ");
// 	printBigInteger(stdout, s8);
	
// //--------------------------------------------------------------------------
// //Negate
// 	printf("\ns2: ");
// 	printBigInteger(stdout, s2);
// 	printf("Negate(s2)\n");
// 	negate(s2);
// 	printf("s2: ");
// 	printBigInteger(stdout, s2);
	
// 	printf("\ns3: ");
// 	printBigInteger(stdout, s3);
// 	printf("Negate(s3)\n");
// 	negate(s3);
// 	printf("s3: ");
// 	printBigInteger(stdout, s3);
	
// 	printf("\ns4: ");
// 	printBigInteger(stdout, s4);
// 	printf("Negate(s4)\n");
// 	negate(s4);
// 	printf("s4: ");
// 	printBigInteger(stdout, s4);
	
// //--------------------------------------------------------------------------
// //copy and compare   
	
// 	printf("\ns5: ");
// 	printBigInteger(stdout, s5);
// 	BigInteger s5c = copy(s5);
// 	printf("Copy of s5: ");
// 	if(equals(s5, s5c) && compare(s5, s5) == 0) 
// 		printf("T\n");
// 	else 
// 		printf("F\n");
// 	freeBigInteger(&s5c);
	
// 	printf("s0: ");
// 	printBigInteger(stdout, s0);
// 	printf("s1: ");
// 	printBigInteger(stdout, s1);
// 	printf("s0 = s1 ? ");
// 	if(equals(s0, s1) && compare(s0, s1) == 0) 
// 		printf("T\n");
// 	else 
// 		printf("F\n");
	
// 	printf("s2: ");
// 	printBigInteger(stdout, s2);
// 	printf("sign of s2 : %d\n", sign(s2));
// 	printf("s0: ");
// 	printBigInteger(stdout, s0);
// 	printf("sign of s0 : %d\n", sign(s0));
// 	printf("s6: ");
// 	printBigInteger(stdout, s6);
// 	printf("sign of s6 : %d\n", sign(s6));
	
	
// 	printf("\ns0: ");
// 	printBigInteger(stdout, s0);
// 	printf("s1: ");
// 	printBigInteger(stdout, s1);
// 	printf("s2: ");
// 	printBigInteger(stdout, s2);
// 	printf("s3: ");
// 	printBigInteger(stdout, s3);
// 	printf("Make Zeros: \n");

// 	makeZero(s0); makeZero(s1); makeZero(s2);
// 	makeZero(s3);
// 	printf("\ns0: ");
// 	printBigInteger(stdout, s0);
// 	printf("s1: ");
// 	printBigInteger(stdout, s1);
// 	printf("s2: ");
// 	printBigInteger(stdout, s2);
// 	printf("s3: ");
// 	printBigInteger(stdout, s3);
	
// 	freeBigInteger(&s0);
// 	freeBigInteger(&s1);
// 	freeBigInteger(&s2);
// 	freeBigInteger(&s3);
// 	freeBigInteger(&s4);
// 	freeBigInteger(&s5);
// 	freeBigInteger(&s6);
// 	freeBigInteger(&s7);
// 	freeBigInteger(&s8);
}
/*
s0: -12345
s1: 12345
s2: -23402
s3: 89325323
s4: 532 222660100
s5: -432532243
s6: 63222 222223120
s7: -4
s8: 1

s0: -12345
s0 = s1 + s0
flip: 0
s0: 0

s2: -23402
s2 = s2 + s1
asd
get(A->L): 12345
get(B->L): 23402
flip: -1
s2: -11057

s1: 12345
s1 = s1 + s1
s1: 24690

s7: -4
s7 = s1 + s1
s7: 49380

s7: 49380
s7 = s5 - s7
s7: -432581623

s7: -432581623
s7 = s4 - s4
flip: 0
s7: 0

s4: 532 222660100
s4 = s4 - s1
flip: 1
s4: 532 222635410

s3: 89325323
s3 = s3 - s3
flip: 0
s3: 0

s1: 24690
s1 = s0 * s1
s1: 0

s5: -432532243
s5 = s5 * s6
s5: -27345 649585610 540058160

s8: 1
s8 = s8 * s8
s8: 1

s2: -11057
Negate(s2)
s2: 11057

s3: 0
Negate(s3)
s3: 0

s4: 532 222635410
Negate(s4)
s4: -532 222635410

s5: -27345 649585610 540058160
Copy of s5: T
s0: 0
s1: 0
s0 = s1 ? T
s2: 11057
sign of s2 : 1
s0: 0
sign of s0 : 0
s6: 63222 222223120
sign of s6 : 1

s0: 0
s1: 0
s2: 11057
s3: 0
Make Zeros:

s0: 0
s1: 0
s2: 0
s3: 0
*/