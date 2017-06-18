#include<stdio.h>

int main() {
	int a[10];
	int b[10];
	int i,j;
	
	for(i = 0; i < 10; i++) {
		a[i] = i;
		b[i] = i;
	}

	for(j = 0; j < 10; j++) {
		a[j] = b[j] + 1;
		printf(" %p R\n",&b[j]);
		printf(" %p W\n",&a[j]);
	}
	
	
}
