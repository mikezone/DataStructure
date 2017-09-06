// 只有二叉树的遍历算法

// 状态定义
typedef int Status;
typedef int Index;
#define ERROR -1
#define OVERFLOW -2 //
#define RangeException -3 // 数组越界
#define OK 0



#include <stdio.h>
#include <stdlib.h>

typedef int TElemType;
typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;


// 先序遍历 递归算法
Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType)) {

    if (T) {
        visit(T->data);
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
        return OK;
    }
    return ERROR;
}
// 中序遍历 递归算法
Status InOrderTraverse(BiTree T, Status (*visit)(TElemType)) {
    if (T) {
        InOrderTraverse(T->lchild, visit);
        visit(T->data);
        InOrderTraverse(T->rchild, visit);
        return OK;
    }
    return ERROR;
}

/////////////////////////////////////////////////////////////非递归


// 非递归算法用到了栈
#define MAXSIZE 100
typedef BiTNode *SElemType;
typedef struct
{
    SElemType data[MAXSIZE];
    int top; /* 用于栈顶指针 */
}SqStack;
// 省略栈的实现 只提供方法原型
Status InitStack(SqStack &S);
bool StackEmpty(SqStack S);
Status Push(SqStack &S, SElemType e);
Status Pop(SqStack &S, SElemType &e);

// 先序遍历 非递归算法 用到了栈
Status PreOrder(BiTree T, Status (*visit)(TElemType)) {
    
    SqStack S; InitStack(S); BiTNode *p = T;
    while (p || !StackEmpty(S)) {
        while (p) {
            visit(p ->data);
            Push(S, p);
            p = p->lchild;
        }
        if (!StackEmpty(S)) {
            Pop(S, p);
            p = p->rchild;
        }
    }
    return OK;
}


// 中序遍历 非递归算法  也用到了栈
Status InOrder(BiTree T, Status (*visit)(TElemType)) {
    SqStack S; InitStack(S); BiTNode *p = T;
    while (p || StackEmpty(S)) {
        if (p) {
            Push(S, p); p = p -> lchild;
        } else {
            Pop(S, p);
            visit(p ->data);
            p = p ->rchild;
        }
    }
    return OK;
}
