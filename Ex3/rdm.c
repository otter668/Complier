/*
 * Copyright (c) 2015 AHPUMEC. All rights reserved.
 * Created by GaoChao <chaogao@ahpumec.edu.cn>.
 * Filename : rdm.c
 * Description : recursive descent method
 * Version : 2.0
 */

#include <stdio.h>
#include <stdlib.h>

char surplus[50];
char in[50];
char curch;
int len_s,len_i;

void E();
void T();
void G();
void S();
void F();
void GetSymbol();
void Match();
void Error(int errNo);
void print_ln(const char pg[]);

int main(void)
{
    int ret;
    char ch = 0;
    len_s = len_i = 0;
    printf("recursive descent program. create by Gaochao,2013***,CS2115\n");
    printf("input a expression within 50 characters which endwith '#':");
    while(ch!='#'){
        ch = getchar();
        if(ch!='\0'){
            surplus[len_s++] = ch;
        }
    }
    printf("Production of grammar\tstring_in\tcharacter\tstring_surplus\n");
    GetSymbol();
    E();
    if(curch=='#'){
        printf("Accepted!\n");
    }
    else{
        Error(2);
    }
    system("pause"); 
    return 0;
}

void E()
{
    print_ln("E->TG");
    T();
    G();
}

void T()
{
    print_ln("T->FS");
    F();
    S();
}

void G()
{
    if(curch=='+'){
        print_ln("G->+TG");
        Match();
        GetSymbol();
        T();
        G();
    }
    else if(curch=='-'){
        print_ln("G->-TG");
        Match();
        GetSymbol();
        T();
        G();
    }
    else{
        print_ln("G->e");
    }
}

void S()
{
    if(curch=='*'){
        print_ln("S->*FS");
        Match();
        GetSymbol();
        F();
        S();
    }
    else if(curch=='/'){
        print_ln("S->/FS");
        Match();
        GetSymbol();
        F();
        S();
    }
    else{
        print_ln("S->e");
    }
}

void F()
{
    if(curch=='i'){
        print_ln("F->i");
        Match();
        GetSymbol();
    }
    else if(curch=='('){
        print_ln("F->(E)");
        Match();
        GetSymbol();
        E();
        if(curch==')'){
            Match();
            GetSymbol();
        }
        else{
            Error(1);
        }
    }
    else{
        Error(0);
    }
}

void GetSymbol()
{
    int i=1;
    curch = surplus[0];
    for(;i<len_s;++i){
        surplus[i-1] = surplus[i];
    }
    len_s--;
}

void Match()
{
    in[len_i++] = curch;
}

void Error(int errNo)
{
    printf("syntax error:%d\n",errNo);
    system("pause");
    exit(1);
}

void print_ln(const char pg[])
{
    int i;
    printf("%-21s\t",pg);
    for(i=0;i<len_i;++i){
        printf("%c",in[i]);
    }
    for(;i<9;++i){
        printf(" ");
    }
    printf("\t    %c    \t",curch);
    for(i=0;i<len_s;++i){
        printf("%c",surplus[i]);
    }
    printf("\n");
}
