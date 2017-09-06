// 静态查找： 顺序查找、折半查找、静态树表查找、索引顺序表查找
// 动态查找: 二叉排序树和平衡二叉树、 B-树和B+树 、键树
// 哈希表


///// 只简单介绍顺序和折半

#include <stdio.h>
// 顺序查找
//  传递参数:  数组、长度、要查找的元素
// 返回参数:所在的索引
int search_seq(int arr[], int length, int key) {
    int i = length - 1;
    for (; arr[i] != key && i >= 0; i--);
    return i; // i < 0则没有找到
}

// 折半查找 只适合于 有序数组
int search_bin(int arr[], int length, int key) {
    int low = 0, high = length;
    while ( low <= high) {
        int mid = (low + high) / 2;
        if ( key == arr[mid] ) return mid;
        if ( key < arr[mid]) high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}


/// test
int main() {
    int arr[] = {10, 20, 30};
    int index = search_seq(arr, 3, 90);
    printf("%d", index);
    
    printf("\n--------\n");
    index = search_bin(arr, 3, 10);
    printf("%d", index);
}



