//
//  main.m
//  DataStructure
//
//  Created by Mike on 2017/8/30.
//  Copyright © 2017年 Mike. All rights reserved.
//

#include <stdio.h>

//void quickSort(int array[], int begin, int end) {
//    if (end - begin <= 0) return;
//
//    int basis = array[begin];
//    int leftPointer = begin;
//    int rightPointer = end;
//
//    bool direction = true; // true means right direction
//
//    while (rightPointer > leftPointer) {
//        if (direction) {
//            bool hasExchanged = false;
//            for (int i = rightPointer; i > leftPointer; i--) {
//                if (array[i] <= basis) {
//                    array[leftPointer++] = array[i];
//                    rightPointer = i;
//                    direction = !direction;
//                    hasExchanged = true;
//                    break;
//                }
//            }
//            if (!hasExchanged)
//            rightPointer = leftPointer; // 一次右侧遍历并没有发现比basis小的元素,跳出循环
//        } else {
//            bool hasExchanged = false;
//            for (int i = leftPointer; i < rightPointer; i++) {
//                if (array[i] >= basis) {
//                    array[rightPointer--] = array[i];
//                    leftPointer = i;
//                    direction = !direction;
//                    hasExchanged = true;
//                    break;
//                }
//            }
//            if (!hasExchanged)
//            leftPointer = rightPointer;
//        }
//
//    }
//    array[rightPointer] = basis;
//    for (int i = 0; i < 6; i++) {
//        printf("%zd ", array[i]);
//        if (i == 5) {
//            printf("\n");
//        }
//    }
//    quickSort(array, begin, rightPointer - 1);
//    quickSort(array, rightPointer + 1, end);
//
//}

//void quickSort(int array[], int begin, int end) {
//    if (end - begin <= 0) return;
//
//    int basis = array[begin];
//    int leftPointer = begin;
//    int rightPointer = end;
//
//    while (leftPointer < rightPointer) {
//        int i = rightPointer;
//        while (i > leftPointer && array[i] >= basis) {
//            i--;
//        }
//        if (array[i] < basis) {
//            array[leftPointer] = array[i];
//        }
//        rightPointer = i;
//
//        int j = leftPointer;
//        while (j < rightPointer && array[j] <= basis) {
//            j++;
//        }
//        if (array[j] > basis) {
//            array[rightPointer] = array[j];
//        }
//        leftPointer = j;
//    }
//
//    array[leftPointer] = basis;
//    for (int i = 0; i < 6; i++) {
//        printf("%zd ", array[i]);
//        if (i == 5) {
//            printf("\n");
//        }
//    }
//    quickSort(array, begin, leftPointer - 1);
//    quickSort(array, leftPointer + 1, end);
//}

void quickSort(int array[], int begin, int end) {
    if (end - begin <= 0) return;
    
    int basis = array[begin];
    int leftPointer = begin;
    int rightPointer = end;
    
    while (leftPointer < rightPointer) {
        while (leftPointer < rightPointer && array[rightPointer] >= basis) {
            rightPointer --;
        }
        array[leftPointer] = array[rightPointer];
        
        while (leftPointer < rightPointer && array[leftPointer] <= basis) {
            leftPointer ++;
        }
        array[rightPointer] = array[leftPointer];
    }
    
    array[leftPointer] = basis;
    
    //    for (int i = 0; i < 6; i++) {
    //        printf("%zd ", array[i]);
    //        if (i == 5) {
    //            printf("\n");
    //        }
    //    }
    
    quickSort(array, begin, leftPointer - 1);
    quickSort(array, leftPointer + 1, end);
}


int main(int argc, const char * argv[]) {
    int arr[] = {10, 1, 3, 7, 4, 5};
    quickSort(arr, 0, 5);
    for (int i = 0; i < 6; i++) {
        printf("%zd ", arr[i]);
    }
    return 0;
}
