//
//  main.cpp
//  栈Stack
//
//  Created by Mike on 15/6/15.
//  Copyright (c) 2015年 Mike. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
/**
 *  状态类型定义
 */
typedef int Status;
typedef int Index;
#define ERROR -1
#define OVERFLOW -2 //
#define RangeException -3 // 数组越界
#define OK 0

#define MAXSIZE 100
typedef int SElemType;
typedef struct
{
    SElemType data[MAXSIZE];
    int top; /* 用于栈顶指针 */
}SqStack;


// 初始化
Status InitStack(SqStack &S)
{
    /* S.data=(SElemType *)malloc(MAXSIZE*sizeof(SElemType)); */
    S.top = -1;
    return OK;
}
// 将栈置空
Status ClearStack(SqStack &S)
{
    S.top = -1;
    return OK;
}
// 栈的长度
int StackLength(SqStack S)
{
    return S.top + 1;
}
// 获取栈顶元素
Status GetTop(SqStack S,SElemType &e)
{
    if (S.top == -1) return ERROR;
    e = S.data[S.top];
    return OK;
}
// 入栈
Status Push(SqStack &S,SElemType e)
{
    if(S.top == MAXSIZE -1) return ERROR; // 栈满
    S.top++;                /* 栈顶指针增加一 */
    S.data[S.top]=e;  /* 将新插入元素赋值给栈顶空间 */
    return OK;
}
// 出栈
Status Pop(SqStack &S,SElemType &e)
{
    if(S.top == -1) return ERROR;
    e = S.data[S.top];   /* 将要删除的栈顶元素赋值给e */
    S.top--;                /* 栈顶指针减一 */
    return OK;
}
// 遍历栈
Status visit(SElemType c)
{
    printf("%d ",c);
    return OK;
}

Status StackTraverse(SqStack &S)
{
    int i = 0;
    while(i <= S.top)
    {
        visit(S.data[i++]);  // 由栈底向栈顶
    }
    printf("\n");
    return OK;
}
int main() {
    SqStack s;
    InitStack(s);
    
    Push(s, 10);
    Push(s, 20);
    StackTraverse(s);
    printf("length == %d\n", StackLength(s));
    
    SElemType e;
    Pop(s, e);
    printf("%d\n",e);
    StackTraverse(s);
    return 0;
}

