/*
 * Using: This is a Compiler for brainfuck
 * Author: xx
 * Time: 2016.10.30
 * Version: 1.0
 */

#include <stdio.h>

char source[1000] = {0};
char distination[1000] = {0};
int count = 0;
int xx = 0;

//interepret function
void interpret(char *ch) {
	int bflag = 0;
	char* d = 0;

	while(*ch) {
		switch(*ch) {
			case '<':
				count = count - 1;
				break;
			case '>':
				count = count + 1;
				break;
			case '+':
				distination[count] = distination[count] + 1;
				break;
			case '-':
				distination[count] = distination[count] - 1;
				break;
			case '.':
				putchar(distination[count]);
				fflush(stdout);
				break;
			case ',':
				distination[count] = getchar();
				fflush(stdout);
				break;
			case '[':
				for(bflag = 1, d = ch; bflag && *ch; ch++) {
					bflag = bflag - (*(ch + 1) == ']');
				}
				if(!bflag) {
					*ch = 0;
					while(distination[count]) {
						interpret(d + 1);
				}
					*ch = ']';
				}
				break;
		}

		ch = ch + 1;
	}
}

int main(int argc, char* argv[]) {
	//Read source from file
	FILE *file;

	if(file = fopen(argv[1], "r")) {
		char ch = '0';
		int i = 0;
		while((ch = getc(file)) > 0) {
			source[i] = ch;
			i = i + 1;
		}
		source[i] = '\0';
		interpret(source);
	}

	return 0;
}
