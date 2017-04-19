#include <stdio.h>
#include <string.h>

#define BUF_SIZE 50
#define SECTION_SIZE 4

int main(int argc, char* argv[]) {
	int length = 0;
	char* str = NULL;

	if(argc != 2) {
		printf("Error: Must two parameters.\n");
		return 0;
	}

	str = argv[1];
	length = strlen(argv[1]);

	for(int i = 0; i < length; i += 1) {
		//print origin string
		if(i%SECTION_SIZE == 0) {
			int j = i;

			printf("\n");
			while(j <= i+SECTION_SIZE-1) {
				printf("%c", *(str + j));
				j += 1;
			}
			printf("\t");
		}	

		//ASCII to hex only tow bits.
		char buf[3] = {0};
		sprintf(buf, "%x", *(str + i));
		printf("\\x%s", buf);
	}

	printf("\n");

	return 0;
}
