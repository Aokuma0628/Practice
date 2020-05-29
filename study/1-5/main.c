/*
	How to use functions and macros with the same name
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int (max)(int a, int b) {
	printf("Function version max2 called\n");
	return a > b ? a :b;
}

int main(void) {
	int x,y;
	char bufx[32], bufy[32];
	int cnt = 0;
	
	printf("x value is ");
	while ((bufx[cnt] = fgetc(stdin)) != '\n'){
		cnt++;
		if (cnt > 31) {
			break;
		}
	}
	bufx[cnt] = '\0';
	cnt = 0;
	
	printf("y value is ");
	while ((bufy[cnt] = fgetc(stdin)) != '\n'){
		cnt++;
		if (cnt > 31) {
			break;
		}
	}
	bufy[cnt] = '\0';
	x = atoi(bufx);
	y = atoi(bufy);
	
	printf("MAX(x, y) = %d\n", MAX(x, y));
	printf("(max)(x, y) = %d\n", (max)(x, y));
	
	return 0;
}