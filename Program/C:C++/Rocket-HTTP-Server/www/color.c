#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char* param;
	char color[32] = {0};

	param = getenv("CONTENT_LENGTH");
	strcpy(color, param+6);		//color=xxxx
	
	printf("<html>\n");
	printf("<head>\n");
	printf("<title>%s</title>\n", color);
	printf("<style>\n");
	printf("body {\n");
	printf("background-color: %s\n;", color);
	printf("}\n");
	printf("</style>\n");
	printf("</head>\n");
	printf("<h1>%s.</h1>\n", color);
	printf("</html>\n");

	return 0;
}
