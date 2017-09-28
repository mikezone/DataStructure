//
//  main.cpp
//  归并排序MergingSort
//
//  Created by Mike on 2017/9/25.
//  Copyright © 2017年 Mike. All rights reserved.
//

#include <iostream>
#include <math.h>

void Merge(int source_array[], int result_array[], int low_index, int sep_index, int high_index) {
    // 将有序的source_array[low..sep]和有序的source_array[sep+1...high]归并为有序的result_array[low...high]
    int left_pointer = low_index, right_pointer = sep_index + 1;
    int result_index = low_index;
    while (left_pointer <= sep_index && right_pointer <= high_index) {
        if (source_array[left_pointer] <= source_array[right_pointer]) {
            result_array[result_index++] = source_array[left_pointer++];
        } else {
            result_array[result_index++] = source_array[right_pointer++];
        }
    }
    while (left_pointer <= sep_index) { // source_array[sep+1...high]遍历完毕
        result_array[result_index++] = source_array[left_pointer++];
    }
    while (right_pointer <= high_index) { // source_array[low...sep]遍历完
        result_array[result_index++] = source_array[right_pointer++];
    }
}

void MergeSort(int source_array[], int result_array[], int low, int high) {
    if (low == high) { // 递归结束条件，只有一个元素
        result_array[low] = source_array[low];
        return;
    }

    int sep = (low + high) / 2;
    int *temp_result = (int *)malloc(sizeof(int) * (high - low + 1));
    MergeSort(source_array, temp_result, low, sep);
    MergeSort(source_array, temp_result, sep + 1, high);
    Merge(temp_result, result_array, low, sep, high);
}

//void MergeSort(int source_array[], int *&result_array, int length) {
//    int *temp_source = (int *)malloc(sizeof(int) * length);
//    memcpy(temp_source, source_array, sizeof(int) * length);
//
//    for (int count_per_g = 1, group_num = length; count_per_g < length; count_per_g *= 2) {
//        int tmep_group_num = group_num;
//
//        int *temp_result = (int *)malloc(sizeof(int) * length);
//        memcpy(temp_result, temp_source, sizeof(int) * length);
//        for (int i = 0; i < group_num && (i+2)*count_per_g - 1 < length; i+=2) {
//            Merge(temp_source, temp_result, i * count_per_g, (i+1) *count_per_g - 1, (i+2)*count_per_g - 1);
//            tmep_group_num --;
//        }
//        temp_source = temp_result;
//
//        group_num = tmep_group_num;
//    }
//    result_array = temp_source;
//}

//void MergeSort(int source_array[], int *&result_array, int length) {
//
//    for (int count_per_g = 1, group_num = length; count_per_g <= length; count_per_g *= 2) {
//        int tmep_group_num = group_num;
//
//        int *temp_result = (int *)malloc(sizeof(int) * length);
//        memcpy(temp_result, source_array, sizeof(int) * length);
//        for (int i = 0; i < group_num && (i+2)*count_per_g - 1 < length; i+=2) {
//            Merge(source_array, temp_result, i * count_per_g, (i+1) *count_per_g - 1, (i+2)*count_per_g - 1);
//            tmep_group_num --;
//        }
//        source_array = temp_result;
//
//        group_num = tmep_group_num;
//    }
//    result_array = source_array;
//}


int main(int argc, const char * argv[]) {
    #define ARRAY_SIZE (6)
    int array[ARRAY_SIZE] = {10, 5, 6, 3, 43, 37};
    int result[ARRAY_SIZE] = {0};
    MergeSort(array, result, 0, ARRAY_SIZE - 1);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%zd ", result[i]);
    }
    return 0;
}

//int main(int argc, const char * argv[]) {
//#define ARRAY_SIZE (6)
//    int array[ARRAY_SIZE] = {10, 5, 6, 3, 43, 37};
//    int *result;
//
//    MergeSort(array, result, ARRAY_SIZE);
//
//    for (int i = 0; i < ARRAY_SIZE; i++) {
//        printf("%d ", result[i]);
//    }
//    return 0;
//}

