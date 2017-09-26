//
//  main.cpp
//  堆排序HeapSort
//
//  Created by Mike on 2017/9/25.
//  Copyright © 2017年 Mike. All rights reserved.
//

#include <iostream>
using namespace std;

/// FTTB
void HeapAdjust(int *array, int array_length, int adjust_index) {
    int value = array[adjust_index];
    for (int i = 2 * adjust_index + 1; i < array_length; i = i*2 + 1) {
        if (i < array_length - 1 && array[i] < array[i+1]) {
            i++; // 右孩子比左孩子大,则将i加1, 用i来记录两者最大值的index
        }
        if (value >= array[i]) { // 如果比两个孩子中最大值都大
            break;
        }
        array[adjust_index] = array[i]; // 将最大孩子上移，这样i位置的槽位就空出了，此时应不急于赋上value的值，而是继续向下调整(继续循环)，找出最下层的位置
        adjust_index = i; // 将要调整的位置下移到有较大值的孩子的位置
    }
    array[adjust_index] = value;
}

void _HeapSort(int *array, int array_length) {
    for (int i = array_length / 2; i > 0; --i) {
        HeapAdjust(array, array_length, i);
    }
    
    for (int i = array_length - 1; i > 0; i--) {
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        
        HeapAdjust(array, i - 1, 0);
    }
}

//////////////////////////////////////////////

int HeapPop(int *&ptr, int array_length) {
    int returnValue = ptr[0];
    ptr[0] = ptr[array_length - 1];
    ptr = (int *)realloc(ptr, sizeof(int) * (array_length - 1));
    HeapAdjust(ptr, array_length, 0);
    return returnValue;
}

void Heapify(int *array, int array_length) {
    for (int i = array_length / 2; i >= 0; --i) {
        HeapAdjust(array, array_length, i);
    }
}

/// 自下向上调整
void HeapAdjustFBTT(int *array, int array_length, int adjust_index) {
    int value = array[adjust_index];
    
    for (int i = (adjust_index + 1)/2 - 1; i < array_length && i >= 0; i = (i + 1)/2 - 1) {
        if (value <= array[i]) {
            break;
        } else {
            array[adjust_index] = array[i];
            adjust_index = i;
        }
    }
    array[adjust_index] = value;
}

void HeapPush(int *&ptr, int array_length, int push_value) {
    ptr = (int *)realloc(ptr, sizeof(int) * (array_length + 1));
    ptr[array_length] = push_value;
    HeapAdjustFBTT(ptr, array_length + 1, array_length);
}

void HeapSort(int *array, int array_length) {
    int *heap = (int *)malloc(sizeof(int) * array_length);
    memcpy(heap, array, sizeof(int) * array_length);
    
    Heapify(heap, array_length);
    
    for (int i = array_length; i > 0; i --) {
        int max = HeapPop(heap, i);
        array[i-1] = max;
    }
}

//////////////////////////////////////////////

int main(int argc, const char * argv[]) {
    #define ARRAY_SIZE (6)
    int array[] = {50, 10, 3, 8, 9, 11};
    
    HeapSort(array, ARRAY_SIZE);
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        cout<<array[i]<<" ";
    }
    
    cout<<endl<<"======================"<<endl;
    
    int *heap = (int *)malloc(sizeof(int) * ARRAY_SIZE);
    memcpy(heap, array, sizeof(int) * ARRAY_SIZE);
    Heapify(heap, ARRAY_SIZE);
    
    HeapPush(heap, ARRAY_SIZE, 17);

    int size = ARRAY_SIZE + 1;
    while (size) {
        cout<<HeapPop(heap, size--)<<" ";
    }
    return 0;
}
