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

/**
 快速排序是对起泡排序的一种改进。它的基本思想是：通过一趟排序将待排记录分割成独立的两部分，其中一部分的值均比另一部分的值小，则可分别对这两部分继续进行排序，以达到整个序列有序。
 它的具体做法是：
 在待排序的序列array中任意选取一个记录(通常是array[0])作为支点(pivot),然后按照下述原则重新排列其余值：
 使用额外空间暂存支点的值；
 将所有小于它的值放在它之前，将所有大于它的值放在它之后，使序列空出支点槽位；
 将支点值放到槽位中。
 则以此槽位为分界点，对左边的序列和对右边的序列分别进行同样的操作。
 
 上述的寻找支点槽位并放置支点值的过程称为一次划分：它的具体做法是：
 设两个指针left_pointer和right_pointer，他们分别从最小索引0和最大索引开始array.length - 1;
 设记录支点的值为pivot_value，并设置它的值为array[0];（当支点的值知道之后，那么一次划分的目标就明确了：让这个值左边的元素都比它小，它右边的都比它大）
 右指针从序列后面向前搜索，若发现一个比pivot_value小的值，则将这个值放到左边，也就是放到left_pointer指向的地方，这时右指针停止向前搜索，此时右指针指向的值已经放到其他位置，这个位置实际上是一个空槽位了；
 左指针向右搜索，发现一个比pivot_value大的值，则将这个值放到右边，也就是放到右指针刚才腾出的空槽位，这时左指针停止向后搜索；
 重复上面的搜索过程，知道左右指针相撞，这个位置就是pivot_value要放入的位置，同时也已经保证左边的值小于pivot_value，而右边的值大于pivot_value。
 这个过程如下图所示：
 */
int _OncePartition(int array[], int low_index, int high_index) {
    
    int pivot_value = array[low_index];
    int left_pointer = low_index;
    int right_pointer = high_index;
    
    while (left_pointer < right_pointer) {
        while (left_pointer < right_pointer && array[right_pointer] >= pivot_value) {
            right_pointer --;
        }
        array[left_pointer] = array[right_pointer];
        
        while (left_pointer < right_pointer && array[left_pointer] <= pivot_value) {
            left_pointer ++;
        }
        array[right_pointer] = array[left_pointer];
    }
    
    // 此时left_pointer == right_pointer == pivot_index
    array[left_pointer] = pivot_value;
    return left_pointer;
}

/**
 * 对于以上的算法，显然left_pointer和right_pointer的声明是多余的，这样只是为了便于理解，而实际上可以直接使用low_index和high_index
 */
int OncePartition(int array[], int low_index, int high_index) {
    
    int pivot_value = array[low_index];
    while (low_index < high_index) {
        while (low_index < high_index && array[high_index] >= pivot_value) {
            high_index --;
        }
        array[low_index] = array[high_index];
        
        while (low_index < high_index && array[low_index] <= pivot_value) {
            low_index ++;
        }
        array[high_index] = array[low_index];
    }
    
    // 此时low_index == high_index == pivot_index
    array[low_index] = pivot_value;
    return low_index;
}


/**
 得到一次划分算法之后，就可以很轻易地写出递归形式的快速排序算法：
 */

void QuickSort(int array[], int low_index, int high_index) {
    if (low_index < high_index) {
        int pivot_index = OncePartition(array, low_index, high_index);
        QuickSort(array, low_index, pivot_index - 1);
        QuickSort(array, pivot_index + 1, high_index);
    }
}

int main(int argc, const char * argv[]) {
    #define ARRAY_SIZE (8)
    int array[] = {49, 38, 65, 97, 76, 13, 27, 49};
    
    QuickSort(array, 0, ARRAY_SIZE);
    
    // print
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%zd ", array[i]);
        if (i == ARRAY_SIZE - 1) {
            printf("\n");
        }
    }
    return 0;
}
/**
 快速排序的平均时间为T(n) = k*n*ln(n),其中n为待排序序列中记录的个数，k为某个常数，经验证明，在所有同数量级(O(n*log(n)))的此类排序方法中，快速排序的常数因子k最小。因此，**就平均时间而言，快速排序是目前被认为是最好的一种内部排序方法**
 
 但是，若初始记录序列按关键字有序或基本有序时,快速排序将蜕化为起泡排序，其时间复杂度为O(n^2)。可依照这几种方法改进：
 ①通常依"三者取中"的法则来选取支点记录，即比较array[low]、array[high]和array[floor((low + high)/2)]这三个值，取三者的中值作为支点值。经验证明，采用“三者取中”的规则可大大改善快速排序在最坏情况下的性能。然而，即使如此，也不能使快速排序在数据有序的情况下达到O(n)的时间复杂度。为此，可按照如下修改“一次划分算法”：
 ②在指针high减一和low增一的同时进行“起泡”操作，即在相邻两个记录处于“逆序”时进行互换，同时在算法中附设两个bool变量分别指示指针low和high在从两端向中间的移动过程中是否进行过交换记录的操作，若指针low在低端向中间的移动过程中没有进行交换记录的操作，则不再需要对低端子表进行排序；类似地，若指针high在从高端向中间的移动过程中没有进行交换记录的操作，则不再需要对高端子表进行排序。这样就能显著改善快速排序的平均性能。
 
 与其他排序方法对比：
 从时间上看，快速排序的平均性能优于前面讨论过的各种排序方法，
 从空间上看，快速排序需要一个栈空间来实现递归。若每一趟排序(划分)都将序列均匀地分割成长度接近的两个子序列，则栈的最大深度为floor(log2(n))+1。但是，若每趟排序之后，支点位置都偏向一端，则最坏情况下栈的最大深度为n。如果在一趟排序之后比较分割所得两部分的长度，且先对长度短的子序列中的记录进行快速排序，则栈的最大深度可降为O(log(n)).
 */

/**
 起泡排序和快速排序的区别：
 
 起泡向端冒泡，快排向支点移动
 起泡每趟拿到的元素是最大值(最小值)，快排每趟拿到的值是不定的，它每趟的重点有两个：
 ①在之后的排序过程去掉支点元素
 ②以支点为界得到两个子序列（子划分）
 */
