//
//  main.cpp
//  动态查找_B-树、B+树
//
//  Created by Mike on 2017/9/24.
//  Copyright © 2017年 Mike. All rights reserved.
//

/*
 AVL树是平衡二叉树，B-树则是平衡的多叉树，而它的结点又比平常的树结点更加复杂。
 B-树是一种平衡的**多路查找树**，它在文件系统中很有用。一棵m阶的B-树，或为空树，或为满足下列特性的m叉树：
 ①树中每个节点至多有m棵子树；
 ②若根结点不是叶子结点，则至少有两棵子树；
 ③除根之外的所有非终端结点至少有ceil(m / 2)棵子树
 ④所有的非终端结点中包含下列信息数据(A: Adress, K: key)
 (n, A0, K1, A1, K2, A2, ..., Kn, An)
 其中：
 K(i) < K(i + 1)
 A(i)为子树根结点的指针，Ai所指的子树中所有值均大于Ki，A(i-1)所指的子树中所有值均小于Ki
 ⑤所有的叶子结点都出现在同一层次上，并且不带信息，其实指向这些结点的指针为空。

 按B-树的定义，3阶的B-树上所有非终端结点之多可有两个元素，至少有一个元素，即子树个数为2或3，因此又称为2-3树。
 
 在B-树上进行查找的过程是一个 顺着指针查找结点 和 在结点数据中进行查找 交叉进行的过程。
 
 */

/////////////////////////////////////////////////////
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define M (3)

#define NOT_FOUND (-1)

typedef int ElemType;
typedef struct BTNode {
    int elem_num;
    struct BTNode *parent;
    ElemType elems[M];
    struct BTNode *ptr[M + 1];
}BTNode, *BTree;

typedef struct {
    BTNode *pt;
    int i;
    bool found_flag;
}Result;

int SearchOnNode(BTNode *&p, ElemType elem);
Result SearchBTree(BTree T, ElemType elem) {
    BTNode *p = T, *q = NULL; // q 用来记录p的双亲
    bool found = false;
    int i = 0;
    while (p && !found) {
        i = SearchOnNode(p, elem);
        
        if (i >= 0 && p->elems[i] == elem) found = true;
        else {
            q = p;
            p = p->ptr[i];
        }
    }
    
    if (found) {
        return {p, i, found};
    } else {
        return {q, i, found};
    }
}

int SearchOnNode(BTNode *&p, ElemType elem) {
    if (!p) return NOT_FOUND;
    int length = p->elem_num;
    int i = 0;
    for (; i < length && p->elems[i] <= elem; i++) {
        if (p->elems[i] == elem) return i;
    }
    return i;
}

/////////////////////////////////////////////////////
typedef int Status;
#define ERROR -1
#define OK 0

void Insert(BTNode *&p, int &i, ElemType e, BTNode *&ap) {
    int cur_length = p->elem_num;
    int insert_index = cur_length;
    while (p->elems[insert_index - 1] > e && insert_index > 0) {
        insert_index --;
    }
    if (p->elems[insert_index - 1] == e) {
        i = insert_index - 1;
        ap = p->ptr[insert_index];
        return;
    }
    int index = cur_length;
    while (index > insert_index) {
        p->elems[index] = p->elems[index - 1];
        index --;
    }
    p->elems[insert_index] = e;
    p->ptr[insert_index + 1] = ap;
    p->elem_num += 1;
    i = insert_index;
}

Status InsertBTree(BTree &T, ElemType e, BTree q, int &i) {
    ElemType x = e;
    BTNode *ap = NULL;
    bool finished = false;
    
    while (q && !finished) {
        Insert(q, i, x, ap);
        if (q->elem_num < M) finished = true;
        else {
            int s = ceil(M / 2.0);
//            split(q, s, ap);
            x = q->elems[s];
            
            q = q->parent;
            if (q) i = SearchOnNode(q, x);
        }
    }
    if (!finished) {
//        NewRoot(T, q, x, ap);
    }
    return OK;
}


/////////////////////////////////////////////////////

// for test
void test_BTree_search() {
    // 构建一棵B-树
    BTNode *root = (BTNode *)malloc(sizeof(BTNode));
    root->elem_num = 1;
    root->elems[0] = 35;
    
    BTNode *lchild = (BTNode *)malloc(sizeof(BTNode));
    lchild->elem_num = 1;
    lchild->elems[0] = 18;
    lchild->ptr[0] = NULL;
    lchild->ptr[1] = NULL;
    
    BTNode *rchild = (BTNode *)malloc(sizeof(BTNode));
    rchild->elem_num = 2;
    rchild->elems[0] = 43;
    rchild->elems[1] = 78;
    rchild->ptr[0] = NULL;
    rchild->ptr[1] = NULL;
    rchild->ptr[2] = NULL;
    
    root->ptr[0] = lchild;
    root->ptr[1] = rchild;
    
    // 查找
    Result result = SearchBTree(root, 43);
    printf("result = {BTNode: %p, i: %zd, tag: %d}\n", result.pt, result.i, result.found_flag);
    
    result = SearchBTree(root, 78);
    printf("result = {BTNode: %p, i: %zd, tag: %d}\n", result.pt, result.i, result.found_flag);
    
    /**
     B-树上进行查找包含两种基本操作：
     ①在B-树上找结点
     ②在结点中找关键字。
     由于B-树通常存储在磁盘上，则前操作①是在磁盘上，而操作②是在内存中进行的，即在磁盘上找到指针p所指结点后，先将接地啊中的信息读入内存，然后在利用顺序查找或折半查找查询等于K的关键字。显然在磁盘上进行一次查找比在内存中进行一次查找耗费时间多的多，因此，在磁盘上进行查找的次数，即**待查关键字所在结点在B-树上的层次数，是决定B-树查找效率的首要因素**。
     含有N个数据元素的B-树上进行查找时，从根节点到元素所在结点的路径上设计的节点数不超过log[ceil(m/2)]((N + 1) / 2 + 1)
     
     **/
}

int main(int argc, const char * argv[]) {
    test_BTree_search();
    return 0;
}
