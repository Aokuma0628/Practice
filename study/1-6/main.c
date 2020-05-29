/*
	Comment out the program by #if 
*/

#include <stdio.h>


#define DEBUG 1

int main (voi) 
{
	int a = 5;
	int x = 1;
	
#if DEBUG == 1
	printf("DEBUG\n");
	a = x;
#endif

	printf("a is %d .\n", a);
	
	return 0;
}