// 静态查找： 顺序查找、折半查找、静态树表查找、索引顺序表查找
// 动态查找: 二叉排序树和平衡二叉树、 B-树和B+树 、键树
// 哈希表


///// 只简单介绍顺序和折半

#include <stdio.h>
// 顺序查找
//  传递参数:  数组、长度、要查找的元素
// 返回参数:所在的索引
int SequentialSearch(int array[], int arr_length, int key) {
    int i = arr_length - 1;
    for (; array[i] != key && i >= 0; i--);
    return i; // i < 0则没有找到
}

int SequentialSearch_Sentinel(int array[], int arr_length, int key) {
    array[0] = key;
    int i = arr_length;
    for (; array[i] != key; i--);
    return i;
}

// 折半查找 只适合于 有序数组
int BinarySearch(int array[], int arr_length, int key) {
    int low = 0, high = arr_length - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if ( key == array[mid] ) return mid;
        if ( key < array[mid]) high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}


/// test
//int main() {
//#define ARRAY_SIZE (3)
//    int array[] = {10, 20, 30};
//    int index = SequentialSearch(array, ARRAY_SIZE, 90);
//    if (index == -1) {
//        printf("没有找到\n");
//    } else {
//        printf("找到了，位置是：%zd\n", index);
//    }
//
//    printf("\n--------\n");
//    index = BinarySearch(array, ARRAY_SIZE, 10);
//    printf("%d", index);
//}

int main() {
#define ARRAY_SIZE (3)
    int array[] = {NULL, 10, 20, 30};
    int index = SequentialSearch_Sentinel(array, ARRAY_SIZE, 90);
    if (index == 0) {
        printf("没有找到\n");
    } else {
        printf("找到了，位置是：%zd\n", index);
    }
    
    printf("\n--------\n");
    index = BinarySearch(array, ARRAY_SIZE, 10);
    printf("%d", index);
}




