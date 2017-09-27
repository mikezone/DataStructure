//
//  main.m
//  B树BST
//
//  Created by Mike on 2017/8/31.
//  Copyright © 2017年 Mike. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

/*
 Binary Search Tree 二叉搜索树
 Binary Sort Tree   二叉排序树
 以上两者是没有区别的，同时又可以叫做"二叉查找树",就是通常所说的BST。
 它具有以下两个特点：
 ①若它的左子树不空，则左子树上所有节点的值均小于它的根节点的值。
 ②若它的右子树不空，则右子树上所有节点的值军大于它的根节点的值。
 ③它的左、右子树也分别为二叉排序树。
 */

////////////////////////////////////////////////////////////////

typedef int Status;
#define TRUE 1
#define FALSE 0
typedef int Index;
#define ERROR -1
#define OVERFLOW -2 //
#define RangeException -3 // 数组越界
#define OK 0

/// 树结构定义
typedef int TElemType;
typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

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

Status visit(TElemType elem) {
    printf("%zd\n", elem);
    return OK;
}

////////////////////////////////////////////////////////////////

BiTree SearchBST(BiTree T, TElemType elem) {
    if (!T || T->data == elem) return T;
    else if (elem < T->data) return SearchBST(T->lchild, elem);
    else return SearchBST(T->rchild, elem);
}

/// 如果查找成功p指向该元素结点，并返回TRUE
/// 如果没有成功，用p记录在访问路径上的最后一个节点，并返回FALSE
/// 指针parent指向T的双亲，其初始调用值为NULL
Status SearchBST(BiTree T, TElemType elem, BiTNode *parent, BiTNode* &p) {
    if (!T) { p = parent; return FALSE; }
    else if (elem == T->data) { p = T; return TRUE; }
    else if (elem < T->data) return SearchBST(T->lchild, elem, T, p);
    else return SearchBST(T->rchild, elem, T, p);
}

Status InsertBST(BiTree &T, TElemType e) {
    BiTNode *p;
    if (!SearchBST(T, e, NULL, p)) { // 如果查找不成功，则插入
        BiTNode *s = (BiTNode *)malloc(sizeof(BiTNode)); // 创建新结点用来存储要插入的值
        s->data = e; s->lchild = s->rchild = NULL;
        if (!p) T = s;
        else if (e < p->data) p->lchild = s;
        else p->rchild = s;
        return TRUE;
    }
    return FALSE; // 查找成功，不需要插入
}
//////// 结合上面三种情况，删除操作的算法如下：
Status Delete(BiTNode *&p);
Status DeleteBST(BiTree &T, TElemType elem) {
    if (!T) return FALSE;
    
    if (elem == T->data) return Delete(T);
    else if (elem < T->data) return DeleteBST(T->lchild, elem);
    else return DeleteBST(T->rchild, elem);
}

Status Delete(BiTNode *&p) {
    if (!p ->rchild) { // 右子树为空
        BiTNode *q = p;
        p = p->lchild;
        free(q);
    } else if (!p->lchild) { // 左子树为空
        BiTNode *q = p;
        p = p->rchild;
        free(q);
    } else { // 左右子树均不空
        BiTNode *q = p;
        BiTNode *s = p ->lchild;
        while (s->rchild) { // 寻找p的前驱
            q = s; // 记录前驱的双亲
            s = s->rchild; // 记录前驱
        }
        p->data = s->data;
        
        if (q != p) q->rchild = s->lchild; // 前驱的双亲是不是p，图一形式
        else q->lchild = s->lchild; // 前驱的双亲是p本身，也就是说：p的前驱就是p的左子树的根节点。
        free(s);
    }
    return TRUE;
}

// for test
void test_BST_search() {
    BiTNode *root = (BiTNode *)malloc(sizeof(BiTNode));
    root->data = 45;
    
    BiTNode *node1 = (BiTNode *)malloc(sizeof(BiTNode));
    node1->data = 12;
    node1->lchild = node1->rchild = NULL;
    
    BiTNode *node2 = (BiTNode *)malloc(sizeof(BiTNode));
    node2->data = 53;
    node2->lchild = node1->rchild = NULL;
    
    root->lchild = node1;
    root->rchild = node2;
    
    TElemType seach_array[] = {0, 45};
    for (int index = 0, length = 2; index < length; index++) {
        TElemType elem = seach_array[index];
        BiTNode *result = SearchBST(root, elem);
        if (result) {
            printf("找到 %zd\n", result->data);
        } else {
            printf("没有找到 %zd\n", elem);
        }
    }
}


void test_BST_insert() {
    BiTree root = NULL; // 一颗空树
    
    TElemType seach_array[] = {45, 24, 53, 45, 12, 24, 90}; // 要查找/插入的值
    for (int index = 0, length = 7; index < length; index++) {
        TElemType elem = seach_array[index];
        InsertBST(root, elem);
    }
    
    // 遍历树
    InOrderTraverse(root, visit); // 通过二叉树的中序遍历，可以得到一个有序序列(这个性质是由二叉排序树的定义决定的)
    
    /*
     这就是说，一个无序序列可以通过构造一颗二叉排序树而变成一个有序序列，构造树的过程即为无序序列进行排序的过程。不仅如此，从上面的插入过程还可以看到，每次插入的新结点都是二叉排序树上新的叶子结点，则在进行插入操作时，不必移动其他结点，仅需改动某个结点的指针，由空变为非空即可。这就相当于在一个有序序列上插入一个记录而不需要移动其他记录。它表明，**二叉排序树既有类似于折半查找的特性，又采用了链表作存储结构，因此是动态查找表的一种适宜表示**。
     同样，在二叉排序树上删去一个结点也是很方便的。对于一般的二叉树来说，删去树中的一个结点是没有意义的。因为它将使以被删结点为根的子树成为森林，破坏了整棵树的结构。然而，对于二叉排序树，删去树上的一个结点相当于删去有序序列中的一个记录，只要在删除某个结点之后依旧保持二叉排序树的特性即可。
     那么，如何在二叉排序上山区一个结点呢？假设在二叉排序树上被删除结点为*p，其双亲的结点为*parent，且不失一般性，可设*p是*parent的左孩子。分三种情况讨论：
     ①若*p结点为叶子结点，修改其双亲结点将p结点置空即可
     ②若*p只有左子树或者只有右子树，让其子树成为其双亲的子树即可
     ③若*p结点的左子树和右子树均不空。
     方法一：设p的左子树为Pl，p的右子树为Pr，让Pl成为p的双亲的左子树，Pr成为Pl的最右结点的右子树，如下图第二行的过程。（如图1）
     方法二：令p的直接前驱替代p，然后再从二叉排序树中删去它的直接前驱。当以直接前驱S替代p时，由于S只有左子树（或没有左子树），则在删去S之后，只要令SL为S的双亲的右子树即可。（如图2）
     */
}

void test_BST_delete() {
    // 构建一棵BST
    BiTree root = NULL;
    TElemType seach_array[] = {45, 24, 53, 45, 12, 24, 90};
    for (int index = 0, length = 7; index < length; index++) {
        TElemType elem = seach_array[index];
        InsertBST(root, elem);
    }
    // 遍历查看
    InOrderTraverse(root, visit);
    
    DeleteBST(root, 45);
    printf("删除了45之后\n");
    InOrderTraverse(root, visit);
    
    DeleteBST(root, 53);
    printf("删除了53之后\n");
    InOrderTraverse(root, visit);
    
    DeleteBST(root, 0);
    printf("0不存在，删除了0之后\n");
    InOrderTraverse(root, visit);

}

int main(int argc, const char * argv[]) {
//    test_BST_search();
    test_BST_insert();
//    test_BST_delete();
    return 0;
}

/*
 含n个节点的二叉排序树的平均查找长度和树的形态有关。
 当先后插入的结点数据元素有序时，构成的二叉排序树蜕变为单枝树。树的深度为n，其平均查找长度为(n + 1) / 2 ，和顺序查找相同，这是最差的情况。
 显然，最好的情况是二叉树的形态和折半查找的判定树相同，其平均查找长度和log2(n)成正比。
 而在随机情况下，二叉树的平均查找长度和log(n)是等数量级的。
 
 为了让二叉排序树的性能接近于随机/最好情况，需要在构成二叉树的过程中进行“平衡化”处理，成为平衡二叉树。
 */
