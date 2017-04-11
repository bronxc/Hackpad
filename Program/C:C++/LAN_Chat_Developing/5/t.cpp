#include <stdio.h>

/*int main()
{
	FILE *fp;
	long size = 0;
	fp = fopen("D:\\1.txt","r");
	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	printf("%ld",size);
	fclose(fp);
	return 0;
}*/
int main()
{
	FILE *fp;
	char str[10];
	fp = fopen("D:\\1.txt","r");
	fread(str,10,1,fp);
	puts(str);
	return 0;
}
