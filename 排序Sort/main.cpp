// 常用的内部排序算法有5大类：插入排序、交换排序、选择排序、归并排序、基数排序

// 插入排序：1.直接插入排序   2. 折半插入、2-路插入排序、表插入   3.希尔排序
// 交换排序：1.起泡排序      2. 快速排序
// 选择排序：1.简单选择排序、 2.树形选择排序      3.堆排序
// 归并排序：2-路归并。。。
// 基数排序：多关键字基数排序、链式基数排序


///// 这里只介绍：1.直接插入排序 2.起泡排序 3.简单选择排序


#include <stdio.h>

/**************************插入类排序*******************************/

/// 直接插入排序
/// 第i趟排序只操作原来数组中的前i+1个元素,每趟操作之后前i+1个元素有序
/// 再继续，则将新取的第i+2个元素插入到前i+1个元素中，使之有序
/// 时间复杂度为O(n^2)
void InsertSort(int array[], int length) {
    for (int i = 1; i < length; i++) {
        int support = array[i]; // 用辅助空间记录每一趟要插入的元素
        int j = i - 1;
        while (array[j] >= support && j >= 0) {
            array[j + 1] = array[j];
            j--;
        }
        if (j == i - 1) continue; // 本身就有序，不需要进行交换
        array[j + 1] = support;
    }
}

/**
 由于第i趟插入之后前i+1个元素有序，所以再插入第i+2个元素时，寻找插入槽位的方法可以改变为在前i+1个元素中进行折半查找(而直接插入排序使用的是顺序查找)，这样先找出要插入的槽位，然后再移动元素，也就是将查找和移动分成了两步。
 这就是折半插入排序.
 它只是减少了比较的次数，而移动的次数和操作和直接插入完全一致。
 时间复杂度是O(n^2)
 */
void BinaryInsertSort(int array[], int length) {
    for (int i = 1; i < length; i++) {
        int support = array[i];
        
        // 折半
        int low = 0, high = i - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (support <= array[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        // 此时low = high + 1 并且是要插入的点
        int j = i - 1;
        while (j >= low) {
            array[j + 1] = array[j];
            j--;
        }
        array[low] = support;
    }
}

///////// 插入类高级算法:希尔排序


/**************************交换类排序*******************************/

//sentinel

/// 起泡排序 (交换排序算法中最简单的一种)
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


/// 简单选择排序 基本上不用   每趟的结果是找到未排序的集合中最小的, 要用到selectMin过程方法
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
#define ARRAY_SIZE (6)
    int array[] = {50, 10, 3, 8, 9, 11};

//    InsertSort(array, ARRAY_SIZE);
    BinaryInsertSort(array, ARRAY_SIZE);
    
    
        //    sort_bubble(array, ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d  ", array[i]);
    }
    return 0;
}
