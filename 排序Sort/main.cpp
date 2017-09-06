// 常用的内部排序算法有5大类：插入排序、交换排序、选择排序、归并排序、基数排序

// 插入排序：1.直接插入排序 2. 折半插入、2-路插入排序、表插入、3.希尔排序
// 交换排序：1.起泡排序 2. 快速排序
// 选择排序：1.简单选择排序、2.树形选择排序、3.堆排序
// 归并排序：2-路归并。。。


///// 只介绍：1.直接插入排序 2.起泡排序 3.简单选择排序

#include <stdio.h>

// 直接插入排序
void sort_insert(int arr[], int length) {

    int temp;// 用temp记录每一趟要插入的元素
    for (int i = 1; i < length; i++) {
        if (arr[i] < arr[i -1]) {
            temp = arr[i];
            arr[i] = arr[i - 1];
            
            
            int j; // 当i - 1位置被空出, 从i-2位置向前找到应该插入的位置
            for (j = i - 2; j >= 0 && temp < arr[j]; --j) {
                arr[j + 1] = arr[j]; // 记录后移
            }
            arr[j + 1] = temp;
        }
    }
}

// 起泡排序 (交换排序算法中最简单的一种)
void sort_bubble(int arr[], int length) {
    for (int i = length - 1, change = true; i >= 1 && change; --i) {
        change = false;
        for (int j = 0; j < i; j++) {
            if (arr[j+1] < arr[j]) {
                int temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
                change = true;
            }
        }
    }
}


// 简单选择排序 基本上不用   每趟的结果是找到未排序的集合中最小的, 要用到selectMin过程方法
int selectMin(int arr[], int length, int startIndex);

void sort_select(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        int j = selectMin(arr, length, i);   // 从索引为i...length-1中找到最小的
        if (i != j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
}
// selectMin的一种实现
int selectMin(int arr[], int length, int startIndex) {
    int minIndex = startIndex;
    for (int i = startIndex + 1; i < length; i++) {
        if (arr[minIndex] > arr[i]) minIndex = i;
    }
    return minIndex;
}



/// test
int main() {
    int arr[] = {50, 10, 3};
    sort_bubble(arr, 3);
    
    for (int i = 0; i < 3; i++) {
        printf("%d  ", arr[i]);
    }
    return 0;
}
