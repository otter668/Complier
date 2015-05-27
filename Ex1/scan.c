//Copyright (c) 2015, Department of computer science and software engineering @ Ahpumec
//Filename : scan.c
//Description : scan a source file by character
//Version : 1.2
//Author : Gaochao
//Date : 2015.5.4
#include <stdio.h>
#include <stdlib.h>

FILE *fp;

char nextChar()
{
	char ch = EOF;
	if(!feof(fp))
	{
		ch = fgetc(fp);
	}
	return ch;
}

int main(void)
{
	char ch;
	if((fp = fopen("scan.c", "r"))==NULL) {
		printf("Error in open a file!");
		exit(1);
	}
	while((ch = nextChar())!=EOF) {
		putchar(ch);
	}
	fclose(fp);
	system("pause");
    return 0;
}
