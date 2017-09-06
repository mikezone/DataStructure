//
//  main.cpp
//  链表LinkedList
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


typedef char ElemType; /* 元素的数据类型，以char类型为例*/

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode, *LinkedList;
// 相当于 typedef struct LNode LNode和 typedef struct LNode *LinkedList;


/// 求链表的长度，链表的第一个节点是没有数据的
int lengthOfLinkedList(LinkedList L) {
    int length = 0; LNode *p = L -> next;
    while (p) {
        length++;
        p = p->next;
    }
    return length;
}
/**
 *  插入方法
 *  在带头结点的单链表中L中index == i的位置前插入元素e
 * index == 0实际上对应着第二个节点
 */
Status insert(LinkedList &L, Index i, ElemType e) {
    int length = lengthOfLinkedList(L);
    if (i < 0 || i > length) {
        return RangeException;
    }
    
    LinkedList p = L; int j = 0;
    while (p ->next && j < i) {
        p = p -> next; ++j;
    }
    
    // j==i!=0
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s -> data = e;
    s -> next = p ->next;
    p -> next = s;
    return OK;
}
/**
 *  获取index == i的元素
 *
 */
Status getElem(LinkedList L, Index i, ElemType &e) {
    
    int length = lengthOfLinkedList(L);
    if (i < 0 || i > length) {
        return RangeException;
    }
    
    LNode *p = L ->next; int j = 0;
    while (p && j < i) {
        p = p -> next; ++j;
    }
    if (!p || j > i) return ERROR;
    e = p -> data;
    return OK;
}
/**
 *  初始化一个链表
 *
 */
Status initLinkedList(LinkedList &L) {
    L = (LNode *)malloc(sizeof(LNode *));
    L -> next = NULL;
    return OK;
}

int main() {
    LinkedList L;
    initLinkedList(L);
    insert(L, 0, 'c');insert(L, 1, 'f'); insert(L, 2, 'd'); insert(L, 4, 'g');
    char e = '\0';
    getElem(L, 0, e);
    printf("%c", e);
    
    getElem(L, 1, e);
    printf("%c", e);
    
    getElem(L, 2, e);
    printf("%c", e);
    
    getElem(L, 4, e);
    printf("%c", e);
    
    
    return 0;
}