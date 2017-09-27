//
//  main.cpp
//  动态查找_平衡二叉树AVL树
//
//  Created by Mike on 2017/9/24.
//  Copyright © 2017年 Mike. All rights reserved.
//

/*
 平衡二叉树(Balanced Binary Tree 或 Height-Balanced Tree, 简写BBT)又称AVL树，AVL树是最先发明的自平衡二叉查找树。它或者是一颗空树，或者是具有以下性质的二叉树：(递归定义)
 ①它的左子树和右子树都是平衡二叉树
 ②且它的左子树和右子树的深度之差不超过1.
 将二叉树上节点的平衡因子BF(Balance Factor)定义为该结点的左子树的深度减去它的右子树的深度，则平衡二叉树上所有结点的平衡因子只可能是-1、0、1。只要二叉树上又一个节点的平衡因子的绝对值大于1，则该二叉树就是不平衡的。
 
 我们希望由任何初始序列构成的二叉排序树都是AVL树。因为AVL树上的任何节点的左右子树的深度之差都不会超过1，则可以证明它的深度和log(n)是同数量级的。由此，它的平均查找长度也和log(n)同数量级。
 
 如何构建一棵AVL树。一般情况下，假设由于在二叉排序树上插入结点而失去平衡的最小子树根结点的指针为a(即a是离插入结点最近，且平衡因子绝对值超过1的祖先结点)，则失去平衡后进行调整的规律可归纳为下列4种情况：
 ①单向右旋平衡处理：由于在a在左子树根结点上插入结点，a 的平衡因子由1增至2，致使以a为根的子树失去平衡，则需进行一次向右的顺时针旋转操作，如下图：
 ②单向左旋平衡处理：由于在a的右子树根节点的右子树上插入结点，a的平衡银子有-1变为-2，致使以a为根节点的子树失去平衡，则需要一次向左的逆时针旋转操作，如下图：
 ③双向旋转(先左后右)平衡处理：由于在a的左子树根节点的右子树上插入结点，a的平衡因子由1增至2，致使以a为根结点的子树失去平衡，则需进行两次旋转(先左旋后右旋)操作，如下图：
 ④双向旋转(先右后左)平衡处理：由于在a的右子树根结点的左子树上插入结点，a的平衡因子由-1变为-2，致使以a为根结点的子树失去平衡，则需进行两次旋转(先右旋后左旋)操作，如下图：
 
 无论是哪一种情况，在经过平衡旋转处理之后，以b或c为根的新子树为平衡二叉树，而且它的深度和插入之前以a为根的子树相同。因此，**当平衡的二叉排序树因插入结点而失去平衡时，仅需对最小不平衡子树进行平衡旋转处理即可。因为经过旋转处理之后的子树深度和插入之前相同，因而不影响插入路径上所有祖先结点的平衡度。**
 
 在平衡的二叉排序树BBST上插入一个新的数据为e的递归算法可描述如下：
 ⑴若BBST为空树，则插入一个新的数据为e的新结点作为BBST的根节点描述的深度增1；
 ⑵若e与BBST跟结点数据相同，则不进行插入；
 ⑶若e小于BBST根节点数据，并且在左子树的所有结点中找不到与之相同的，则将e插入到BBST的左子树上，并且插入之后左子树的深度+1时，分以下几种情况处理：
 ①BBST的根结点的平衡因子为-1(右子树的深度大于左子树的深度)：则将根结点的平衡因子更改为0，BBST的深度不变；
 ②BBST的根结点的平衡因子为0(左右子树的深度相等)：则将根结点的平衡因子更改为0，树的深度不变；
 ③BBST的根结点的平衡因子为1(左子树的深度大于右子树的深度)：若BBST的左子树根结点的平衡因子为1，则需要进行单向右旋平衡处理，并且在右旋处理之后要将根结点和其右子树根结点的平衡因子更改为0，树的深度不变；
 若BBST的左子树根结点的平衡因子为-1，则需进行先向左、后向右的双向旋转平衡处理，并且在旋转处理之后，修改根结点和其左、右子树根结点的平衡因子，树的深度不变；
 ⑷若e大于BBST根节点数据，并且在右子树的所有结点中找不到与之相同的，则将e插入到BBST的右子树上，并且插入之后右子树的深度+1时，其处理方式与⑶对称
 
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////

typedef int Status;
typedef int Index;
#define OK (1)
#define ERROR (-1)

#define INSERT_SUCCESS (1)
#define INSERT_FAILURE (0)

typedef int ElemType;

typedef struct AVLTNode {
    ElemType data;
    int bf;
    struct AVLTNode *lchild, *rchild;
}AVLTNode, *AVLTree;

void InOrderTraverse(AVLTree T, void (*visit)(ElemType)) {
    if (T) {
        InOrderTraverse(T->lchild, visit);
        visit(T->data);
        InOrderTraverse(T->rchild, visit);
    }
}

void visit(ElemType elem) {
    printf("%zd ", elem);
}


////////////////////////////////////////////////////////////////


void R_Rotate(AVLTree &p) {
    AVLTNode *lc = p->lchild;
    p->lchild = lc->rchild;
    lc->rchild = p;
    p = lc;
}

void L_Rotate(AVLTree &p) {
    AVLTNode *rc = p->rchild;
    p->rchild = rc->lchild;
    rc->lchild = p;
    p = rc;
}

#define LH (1)
#define EH (0)
#define RH (-1)

void LeftBalance(AVLTree &T);
void RightBalance(AVLTree &T);
Status InsertAVL(AVLTree &T, ElemType e, bool &taller) {
    if (!T) {
        T = (AVLTNode *)malloc(sizeof(AVLTNode));
        T -> data = e;
        T->lchild = T->rchild = NULL;
        T->bf = EH;
        taller = true;
        return INSERT_SUCCESS;
    }
    
    if (e == T->data) {
        taller = false;
        return INSERT_FAILURE;
    }
    
    if (e < T->data) {
        if (!InsertAVL(T->lchild, e, taller)) {
            return INSERT_FAILURE;
        }
        if (taller) {
            switch (T->bf) {
                case LH:
                    LeftBalance(T);
                    taller = false;
                    break;
                case EH:
                    T->bf = LH;
                    taller = true;
                    break;
                case RH:
                    T->bf = EH;
                    taller = false;
                    break;
                default:
                    break;
            }
        }
    } else { // e > T->data
        if (!InsertAVL(T->rchild, e, taller)) {
            return INSERT_FAILURE;
        }
        if (taller) {
            switch (T->bf) {
                case LH:
                    T->bf = EH;
                    taller = false;
                    break;
                case EH:
                    T->bf = RH;
                    taller = true;
                    break;
                case RH:
                    RightBalance(T);
                    taller = false;
                    break;
                default:
                    break;
            }
        }
    }
    return INSERT_SUCCESS;
}

void LeftBalance(AVLTree &T) {
    AVLTNode *lc = T->lchild;
    switch (lc->bf) {
        case LH: // 情况a，单次右旋即可
            T->bf = lc->bf = EH; // 最终：T 和 T的左子树 的平衡因子都变成0
            R_Rotate(T);
            break;
        case RH: // 左子树根节点的右子树插入，情况c，先左旋再右旋
        {
            AVLTNode *rd = lc->rchild; // rd 为左子树根节点的右子树根节点
            switch (rd->bf) {
                case LH: // 插入点为左子树的根节点的右子树的左子树，与图c情况完全一致
                    T->bf = RH;
                    lc->bf = EH;
                    break;
                case EH:
                    T->bf = lc->bf = EH;
                    break;
                case RH: // 插入点为左子树的根节点的右子树的右子树，将图c插入点变成CR
                    T->bf = EH;
                    lc->bf = LH;
                    break;
                default:
                    break;
            }
            rd->bf = EH;
            L_Rotate(T->lchild);
            R_Rotate(T);
            break;
        }
        default:
            break;
    }
}

void RightBalance(AVLTree &T) {
    AVLTNode *rc = T->lchild;
    switch (rc->bf) {
        case RH: // 情况c，单次左旋即可
            T->bf = rc->bf = EH; // 最终：T 和 T的右子树 的平衡因子都变成0
            L_Rotate(T);
            break;
        case LH: // 左子树根节点的右子树插入，情况c，先左旋再右旋
        {
            AVLTNode *ld = rc->lchild; // ld 为右子树根节点的左子树根节点
            switch (ld->bf) {
                case LH: // 插入点为右子树的根节点的左子树的左子树，与图d情况完全一致
                    T->bf = EH;
                    rc->bf = RH;
                    break;
                case EH:
                    T->bf = rc->bf = EH;
                    break;
                case RH: // 插入点为右子树的根节点的左子树的右子树，将图d插入点变成CR
                    T->bf = LH;
                    rc->bf = EH;
                    break;
                default:
                    break;
            }
            ld->bf = EH;
            R_Rotate(T->rchild);
            L_Rotate(T);
            break;
        }
        default:
            break;
    }
}
////////////////////////////////////////////////////////////////

Status SearchAVL(AVLTree &T, ElemType e, AVLTNode* &node, bool &taller) {
    if (!T) {
        T = (AVLTNode *)malloc(sizeof(AVLTNode));
        T -> data = e;
        T->lchild = T->rchild = NULL;
        T->bf = EH;
        taller = true;
        node = T; // ①
        return INSERT_SUCCESS;
    }
    
    if (e == T->data) {
        taller = false;
        node = T; // ②
        return INSERT_FAILURE;
    }
    
    if (e < T->data) {
        if (!SearchAVL(T->lchild, e, node, taller)) {
            return INSERT_FAILURE;
        }
        if (taller) {
            switch (T->bf) {
                case LH:
                    LeftBalance(T);
                    taller = false;
                    break;
                case EH:
                    T->bf = LH;
                    taller = true;
                    break;
                case RH:
                    T->bf = EH;
                    taller = false;
                    break;
                default:
                    break;
            }
        }
    } else { // e > T->data
        if (!SearchAVL(T->rchild, e, node, taller)) {
            return INSERT_FAILURE;
        }
        if (taller) {
            switch (T->bf) {
                case LH:
                    T->bf = EH;
                    taller = false;
                    break;
                case EH:
                    T->bf = RH;
                    taller = true;
                    break;
                case RH:
                    RightBalance(T);
                    taller = false;
                    break;
                default:
                    break;
            }
        }
    }
    node = T; // ③
    return INSERT_SUCCESS;
}

////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {
    
    // 构建一棵AVL树
    AVLTNode *root = NULL;
    ElemType insert_array[] = {45, 24, 53}; // 要查找/插入的值
    bool grow_taller;
    for (int index = 0, length = 3; index < length; index++) {
        ElemType elem = insert_array[index];
        InsertAVL(root, elem, grow_taller);
    }
    InOrderTraverse(root, visit);
    
    // 再插入
    printf("\n===================");
    InsertAVL(root, 45, grow_taller);
    printf("\n插入 45 之后\n");
    InOrderTraverse(root, visit);
    
    InsertAVL(root, 12, grow_taller);
    printf("\n插入 12 之后\n");
    InOrderTraverse(root, visit);
    
    InsertAVL(root, 24, grow_taller);
    printf("\n插入 24 之后\n");
    InOrderTraverse(root, visit);
    
    InsertAVL(root, 90, grow_taller);
    printf("\n插入 90 之后\n");
    InOrderTraverse(root, visit);
    printf("\n===================\n");
    
    AVLTNode *node;
    ElemType search_array[] = {24, 0, 19};
    for (int index = 0, length = 3; index < length; index++) {
        ElemType elem = search_array[index];
        
        if (SearchAVL(root, elem, node, grow_taller)) {
            printf("没有找到%zd,已经插入\n", elem);
        } else {
            printf("找到%zd\n", node->data);
        }
    }
    printf("现在中序遍历为：");
    InOrderTraverse(root, visit);
    
    return 0;
}

/*
 在平衡树上进行查找的过程和排序树相同，因此，在查找的过程中和给定值进行比较的关键字个数不超过树的深度。
 在平衡树上进行查找的时间复杂度为O(logn)
 */
