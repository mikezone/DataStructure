/*
 * 树：树是n（n>=0）个节点的有限集，在任意一颗非空树中：
 * ①有且仅有一个特定的成为根（Root）的节点
 * ②当n>1时，其余节点可分为m（m>0）个互不相交的有限集T1, T2, ...，其中每个集合本身又是一棵树，并且称为根的子树。
 *
 *
 * 度：节点拥有的子树数称为节点的度，degree。
 * 层次：根为第一层，它的孩子为第二层，以此类推，level。
 * 深度、高度：树中的节点的最大层次称为树的深度或高度，depth。
 * 有序树、无序树：树中节点的子树看成是从左到右有次序的，则称该树为有序树；否则为无序树。
 * 森林：是m(m>=0)棵互不相交的树的集合。
 *
 *
 * 二叉树：是一种特别的树形结构，它的特点是：
 * ①每个节点至多只有两棵子树（即二叉树中不存在度大于2的节点）
 * ②二叉树的子树有左右之分，其次序不能任意颠倒
 *
 * 满二叉树：一棵深度为k且有2**k - 1个节点的二叉树称为满二叉树。
 * 完全二叉树：对满二叉树自根节点按自上而下、自左至右的顺序给节点编号，每一个节点都与在满二叉树的顺序一一对应时，这样的二叉树称为完全二叉树。
 * 完全二叉树的特点是：
 * ①叶子节点只能在层次最大的两层上出现
 * ②任一节点，若其右分支下的子孙的最大层次为l，则其左分支下的子孙的最大层次为l或l+1
 *
 *
 * 二叉树的性质：
 * ①第i层上至多有2**（i-1）个节点（i>=1）
 * ②深度为k的二叉树至多有2**k -1 个节点
 * ③任何一棵二叉树，如果其终端节点数为n0,度为2的节点数为n2，则n0 = n2 + 1
 * ④具有n个节点的完全二叉树的深度为floor(log2(n)) + 1
 * ⑤完全二叉树的节点个数为n,由根节点从1开始编号
 *  若i=1，i为根节点，无双亲；若i>1，双亲是floor(i / 2)
 *  若2i>n,则节点i无左孩子，否则其做孩子节点是2i
 *  若2i+1>n,则节点i无有孩子，否则其有孩子的节点是2i+1
 */



// 这里只有二叉树的遍历算法

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
