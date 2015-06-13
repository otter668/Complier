/*
 * Copyright (c) 2015 AHPUMEC. All rights reserved.
 * Created by GaoChao <chaogao@ahpumec.edu.cn>.
 * Filename : nrdm.c
 * Description : non recursive descent method 
 * Version : 2.0
 */
 
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char left;
    const char *right;
    int len;
} table_e;
table_e table[5][8];
char stack[50];
char surplus[50];
int stack_ptr,length;
char vt[8]={'+','-','*','/','(',')','i','#'};
char vn[5]={'E','T','G','S','F'};

void ExitWithStop(int erno)
{
    system("pause");
    exit(erno);
}

void Push(char ch) {
    if (stack_ptr<50) {
        stack[++stack_ptr] = ch;
    }
    else {
        printf("Error:stack is full!\n");
        ExitWithStop(1);
    }
}

char Pop() {
    char ch = stack[stack_ptr];
    if (stack_ptr>0) {
        stack[stack_ptr--] = 0;
    }
    else {
        printf("Error:stack is empty!\n");
        ExitWithStop(1);
    }
    return ch;
}

int GetCharInVt(char curch) {
    int i;
    for (i = 0; i < 8; ++i) {
        if (vt[i]==curch) {
            return i;
        }
    }
    return -1;
}

int GetCharInVn(char top) {
    int i;
    for (i = 0; i < 5; ++i) {
        if (vn[i]==top) {
            return i;
        }
    }
    return -1;
}

void PrintError() {
    printf("%-12s\t%-19s\tError!\n",stack,surplus);
    ExitWithStop(1);
}

char ShiftLeft() {
    int i;
    for (i = 1; i <= length; ++i) {
        surplus[i-1] = surplus[i];
    }
    --length;
    return surplus[0];
}

void Predict() {
    char curch,top;
    int i,l,t,flag;
    flag = 1;
    curch = surplus[0];
    while (flag) {
        top = stack[stack_ptr];
        if (GetCharInVt(top)!=-1) {
            if (top == curch) {
                if ('#' == curch) {
                    flag = 0;
                }
                else {
                    printf("%-12s\t%-19s\tmatch with %c\n",stack,surplus,curch);
                    Pop();
                    curch = ShiftLeft();
                }
            }
            else {
                PrintError();
            }
        }
        else {
            l = GetCharInVn(top);
            t = GetCharInVt(curch);
            if (table[l][t].left!='\0') {
                printf("%-12s\t%-19s\t%c->%s\n",stack,surplus,table[l][t].left,table[l][t].right);
                Pop();
                for (i = table[l][t].len-1; i >=0; --i) {
                    Push(table[l][t].right[i]);
                }
            }
            else {
                PrintError();
            }
        }
    }
    printf("%-12s\t%-19s\tAccpet!\n",stack,surplus);
}

void InitializeTable() {
    int i,j;
    table_e ele = {'\0', "", 0};
    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 8; ++j) {
            table[i][j] = ele;
        }
    }
    table[0][4]=table[0][6]=(table_e){'E', "TG", 2};
    table[1][4]=table[1][6]=(table_e){'T', "FS", 2};
    table[2][0]=(table_e){'G', "+TG", 3};
    table[2][1]=(table_e){'G', "-TG", 3};
    table[2][5]=table[2][7]=(table_e){'G', "^", 0};
    table[3][2]=(table_e){'S', "*FS", 3};
    table[3][3]=(table_e){'S', "/FS", 3};
    table[3][0]=table[3][1]=table[3][5]=table[3][7]=(table_e){'S', "^", 0};
    table[4][4]=(table_e){'F', "(E)", 3};
    table[4][6]=(table_e){'F', "i", 1};
}

int main(void)
{
    int ch = 0;
    length = 0;
    printf("non recursive descent program. create by Gaochao,2013***,CS2115\n");
    printf("input a expression within 50 characters which endwith '#':");
    while(ch!='#') {
        ch = getchar();
        if ('+' != ch && '-' != ch && '*' != ch && '/' != ch && '(' != ch && ')' != ch && 'i' != ch && '#' != ch) {
            printf("There are some wrong characters!");
            ExitWithStop(1);
        }
        else {
            surplus[length++] = ch;
        }
    }
    surplus[length] = 0;
    printf("Stack\t\tThe remaining string\tAction\n");
    stack_ptr = 0;
    stack[0] = '#';
    Push('E');
    InitializeTable();
    Predict();
    system("pause");
    return 0;
}