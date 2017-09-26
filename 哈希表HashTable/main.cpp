//
//  main.cpp
//  哈希表HashTable
//
//  Created by Mike on 2017/9/25.
//  Copyright © 2017年 Mike. All rights reserved.
//

#include <iostream>

/**
 常规的查找方法建立在比较的基础上，折半查找、二叉排序树查找、B-树查找都是这样的情况。查找的效率依赖于查找过程中所进行的比较次数。
 理想的情况是希望不经过任何比较，一次存取便能得到所查记录，那就必须在记录的存储位置和它的关键字之间建立一个确定的对应关系f，使得每个关键字和结构中一个唯一的存储位置相对应。因而在查找时，只要根据这个对应关系f找到给定值K的像f(K)。若结构中存在关键字和K相等的记录，则必定在f(K)的存储位置上，由此，不需要进行比较便可直接取得所查记录。再次，我们称这个对应关系f为哈希(Hash)函数，按这个思想建立的表成为哈希表。
 Hash:关键字与数据存储位置的映射关系
 HashTable:依照Hash函数维持的数据表。
 
 对于不同的关键字可能得到同一哈希地址，即key1 != key2，而f(key1) = f(key2),这种现象称为冲突(collision).具有相同函数值的关键字该改哈希函数来说成为做同义词。
 
 加上冲突与处理冲突等概念，可以这样描述哈希表：
 根据设定的哈希函数H(key)和处理冲突的方法将一组关键字映像到一个有限的连续的地址集（区间）上，并以关键字在地址集中的"像"作为记录在表中的存储位置，这种表便成为哈希表，这一映像过程称为哈希造表或散列，所得存储位置称哈希地址或散列地址。
 
 在建造哈希表时，不仅要设定一个好的哈希函数，而且要设定一种处理冲突的方法。
 
哈希函数的构造方法：
①直接定址法 H(key) = a * key + b, 极少使用
②数字分析法
③平方取中法， 较常用
④折叠法 （移位叠加、间界叠加）
⑤除留余数法 (一般情况下，可以选p为质数或不包含小于20的质因数的合集)，简单常用
⑥随机数法

不同哈希函数的选取，主要考虑有：
①计算哈希函数所需时间(包括硬件指令的因素)
②关键字的长度
③哈希表的大小
④关键字的分布情况
⑤记录的查找频率

解决冲突的方法：
1.开放定址法
 ①地址+1②di = 1, -1, 4, -4, 9, -9,..③伪随机树序列
2.再哈希法
3.链地址法**
4.建立一个公共溢出区
 
二次聚集：
 在处理冲突过程中发生的，两个第一个哈希地址不同的记录争夺同一个后继哈希地址的现象称作“二次聚集”。
 
*/

//  ---- 开放定制法=哈希表的存储结构----
#define SUCCESS (1)
#define FAILURE (0)
#define DUPLICATE (-1)
typedef int Status;

typedef int KeyType;
#define NULLKEY (-9999999)
typedef int ValueType;
typedef struct {
    KeyType key;
    ValueType value;
}ElemType;

int hashsize[] = {499, 997, 2179, 4297}; // 哈希表容量递增表，一个合适的素数序列
typedef struct {
    ElemType *elems; // 数据元素的存储基址，动态分配数组
    int count; // 当前数据元素个数
    int size_index; // hashsize[size_index]为当前容量
}HashTable;

/// Hash函数，这里使用"除留余数法"
int Hash(KeyType K) {
    return K % 13;
}

/// 解决冲突函数，这里使用"开放定址法"，地址+1
void collision(HashTable H, int &position, int count) {
    position = (position + 1) % hashsize[H.size_index];
}

typedef struct {
    bool success;
    ElemType elem;
}SearchResult;

SearchResult SearchHash(HashTable H, KeyType K, int &position, int &count) {
    position = Hash(K);
    while (position < H.count && H.elems[position].key != NULLKEY && K != H.elems[position].key) {
        collision(H, position, ++count); // position不断被修改为下一次探查的地址
    }
    if (K == H.elems[position].key) {
        return {true, H.elems[position]};
    } else {
        return {false, NULL};
    }
}

Status InsertHash(HashTable &H, ElemType e) {
    int count = 0;
    int p = 0; // 假设初始插入位置为0,会在查找过程中修改
    if (SearchHash(H, e.key, p, count).success) {
        return DUPLICATE; // 已经存在这个元素
    }
    if (count < hashsize[H.size_index]/2) {
        H.elems[p] = e;
        ++H.count;
        return SUCCESS;
    } else {
//        RecreateHashTable(H); // 冲突次数过多，哈希表扩充/重建哈希表
        return FAILURE;
    }
}

// for test
Status InsertKVPair(HashTable &H, KeyType key, ValueType value) {
    ElemType kv = {key, value};
    return InsertHash(H, kv);
}

// for test
void print_hash_table(HashTable &H) {
    printf("count: %zd\n", H.count);
    
    int count = H.count;
    ElemType *p = H.elems;
    printf("KVpair:\n{\n");
    while (count--) {
        printf("%zd: %zd\n", p[H.count - count].key, p[H.count - count].value);
    }
    printf("}\n");
    
}

int main(int argc, const char * argv[]) {
//    int *p = {};
//    p = (int *)realloc(p, sizeof(int));
//    p[0] = 10;
//    printf("%zd", p[0]);
//    p[1] = 12;
//    printf("%zd", p[1]);
    
    ElemType *p = (ElemType *)malloc(sizeof(ElemType));
    HashTable hash_table = {p, 0, 0};
    InsertKVPair(hash_table, 1, 11);
    InsertKVPair(hash_table, 2, 12);
    InsertKVPair(hash_table, 3, 13);
    
    print_hash_table(hash_table);
    printf("===================\n");
    
    int insert_position = 0;
    int collision_count = 0;
    
    KeyType search_keys[] = {1, 3, 5};
    for (int i = 0, length = 3; i < length; i++) {
        KeyType key = search_keys[i];
        SearchResult result = SearchHash(hash_table, key, insert_position, collision_count);
        if (result.success) {
            printf("找到了 value:%zd\n", result.elem.value);
        } else {
            printf("没有找到 key为%zd对应的值\n", key);
        }
    }
    
    return 0;
}

/*
 "线性探测再散列"在处理冲突的过程中易产生记录的二次聚集，使得哈希地址不同的记录又产生新的冲突；
 而"链地址法"处理冲突不会发生类似的情况，因为哈希地址不同的记录在不同的链表中。
 
 在一般情况下，处理冲突方法相同的哈希表，其平均查找长度依赖于哈希表的装填因子：
 哈希表的装填因子定义为：
 α = 表中填入的记录数 / 哈希表的长度
 它标志这哈希表的装满程度。直观的看，α越小，发生冲突的可能性就越小。
 
 哈希表的平均查找长度是α的函数而不是n(填入记录数)的函数。由此，不管n多大，我们总可以选择一个合适的装填因子以便将平均查找长度限定在一个范围内。
 
 值得提醒的是，若要在非链地址处理冲突的哈希表中删除一个记录，则需在该记录的位置上填入一个特殊的符号，以免找不到在它之后填入的“同义词”的记录。
 对于预先知道且规模不大的关键字集，有时也可以找到不发生冲突的哈希函数，因此，对频繁进行查找的关键字集，还是尽力设计一个完美的哈希函数。
 */


/////////////////////////////////////////////////////////
/**
 哈希表在程序开发有广泛的应用，但是要注意的是：
 哈希表可以用来实现各个编程语言中的字典类型，但是不代表字典类型就是哈希表来实现的。
 
 Java中的HashMap是按照哈希表的原理实现的，http://www.importnew.com/18633.html
    TreeMap是用红黑树实现的
    但是Java中依然有Hashtable，不过它的用法与HashMap相似，除了线程同步问题外，Hashtable基本可以认为是历史遗留产物，自Java 2重新设计结合框架开始：ArrayList代替Vector，LinkedList代替Stack，HashMap代替HashTable
 
 Python中的dict
 
 OC中的NSDictionary
 Swift中的Dictionary
 他们的实现是否是使用哈希表，可以查看CFDictionary源码查看, Swift这部分开源了吗
 https://github.com/apple/swift/blob/master/stdlib/public/SDK/Foundation/NSDictionary.swift
 OC和Swift中还有NSHashTable和NSMapTable
 NSHashTable 并不是以包含键值对的数据为元素而建立的表，这与我们说的哈希表太不相同，而它的是扩展了更多方式的内存管理的高级NSSet。
 NSMapTable 则是有更多内存管理方式的高级NSDictionary。这样说来NSMapTable和NSDictionary倒更像是哈希表的实现。
 http://www.isaced.com/post-235.html
 
 C++中的std::map
 
 
 */
