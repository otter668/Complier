/*
 * Copyright (c) 2015 AHPUMEC. All rights reserved.
 * Created by GaoChao <chaogao@ahpumec.edu.cn>.
 * Filename : la.c
 * Description : lexical analysis
 * Version : 2.0
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define FILENAME "example.c"
#define MODE "r"

const char *key[] = {"int","char","float","double","if","else","for","while","return"};
const char *border[]={",",";","{","}","(",")"};
const char *arithmetic[]={"+","-","*","/","<","<=","=",">",">=","<>"};

FILE* fp;

char nextChar()
{
    char ch = EOF;
    if(!feof(fp)){
        ch = fgetc(fp);
    }
    return ch;
}

int isin(char str[], int type)
{
    int i = 0;
    switch(type){
        case 1:{
            for(i=0;i<9;++i){
                if(strcmp(str,key[i])==0){
                    return i+1;
                }
            }
            break;
        }
        case 4:{
            for(i=0;i<10;++i){
                if(strcmp(str,arithmetic[i])==0){
                    return i+1;
                }
            }
            break;
        }
        case 5:{
            for(i=0;i<6;++i){
                if(strcmp(str,border[i])==0){
                    return i+1;
                }
            }
            break;
        }
    }
    return 0;
}

char alphaprocess(char ch) {
    char buffer[1024];
    int bufPtr = 0;
    while(isalpha(ch)||isdigit(ch)||'_'==ch){
        buffer[bufPtr++] = ch;
        ch = nextChar();
    }
    buffer[bufPtr] = '\0';
    if(isin(buffer,1)){
        printf("(1, \"%s\")\n",buffer);
    }
    else{
        printf("(2, \"%s\")\n",buffer);
    }
    return ch;
}

char digitprocess(char ch) {
    char buffer[1024];
    int bufPtr = 0;
    while(isdigit(ch)||'.'==ch){
        buffer[bufPtr++] = ch;
        ch = nextChar();
    }
    buffer[bufPtr] = '\0';
    printf("(3, \"%s\")\n",buffer);
    return ch;
}

char otherprocess(char ch) {
    char buffer[3];
    buffer[0] = ch;
    buffer[1] = buffer[2] = '\0';
    char lookahead = nextChar();
    if(isspace(ch)){
        return lookahead;
    }
    else if(isin(buffer,5)){
        printf("(5, \"%s\")\n",buffer);
    }
    else if(isin(buffer,4)) {
        buffer[1] = lookahead;
        if(isin(buffer,4)) {
            lookahead = nextChar();
            printf("(4, \"%s\")\n",buffer);
        }
        else{
            buffer[1] = '\0';
            ungetc(lookahead,fp);
            printf("(4, \"%s\")\n",buffer);
        }
    }
    return lookahead;
}

int main(void)
{
    char ch;
    if((fp=fopen(FILENAME,MODE))==NULL){
        printf("Error:File does not exist.");
    }
    ch=nextChar();
    while(ch!=EOF){
        if(isalpha(ch)){
            ch = alphaprocess(ch);
        }
        else if(isdigit(ch)){
            ch = digitprocess(ch);
        }
        else{
            ch = otherprocess(ch);
        }
    }
    fclose(fp);
    system("pause");
    return 0;
}
