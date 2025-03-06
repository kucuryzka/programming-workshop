#include <stdio.h>
#include "functions.h"

int main(void){
	int a, b;
	double(*func) (double) = root;
	printf("Enter the beginning and the end of the segment:");
	scanf("%i", &a);
	scanf("%i", &b);

	printf("definite integral equals: %f", func1(a, b, func));
	
	return 0;
};




