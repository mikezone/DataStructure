//
//  main.cpp
//  哈希表HashTable
//
//  Created by Mike on 2017/9/25.
//  Copyright © 2017年 Mike. All rights reserved.
//

#include <iostream>
/**
哈希函数的构造方法：
直接定址法
数字分析法
平方取中法
折叠法
除留余数法
随机数法

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

int Hash(KeyType K) {
    return K % 13;
}

void collision(int &position, int count) {
    position++;
}

typedef struct {
    bool success;
    ElemType elem;
}SearchResult;

SearchResult SearchHash(HashTable H, KeyType K, int &position, int &count) {
    position = Hash(K);
    while (position < H.count && H.elems[position].key != NULLKEY && K != H.elems[position].key) {
        collision(position, ++count);
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
//        RecreateHashTable(H); // 哈希表扩充
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
