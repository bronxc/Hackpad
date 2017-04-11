#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAYMAX 10

int main(int argc, char* argv[]) {
	int source[ARRAYMAX] = {7, 2, 5, 1, 3, 5, 0, 5, 8, 0};
	char* p = NULL;
	int i = 0;
	int num = 0;

	p = (char*)malloc(ARRAYMAX * sizeof(char));
	if(p == NULL) {
		printf("malloc failed\n");
	}
	memset(p, 0, ARRAYMAX * sizeof(char));

	for(i = 0; i < ARRAYMAX; i++) {
		*(p + source[i]) = 1;
	}

	printf("list: \n");
	for(i = 0; i < ARRAYMAX; i++) {
		printf("%d ", *(p + i));
	}
	printf("\b\n");

	scanf("%d", &num);

	if(*(p + num) == 1) {
		printf("Exists\n");
	}
	else {
		printf("Not Exists\n");
	}

	free(p);

	return 0;
}
