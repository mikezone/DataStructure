// 常用的内部排序算法有5大类：插入排序、交换排序、选择排序、归并排序、基数排序

// 插入排序：1.直接插入排序   2. 折半插入、2-路插入排序、表插入   3.希尔排序
// 交换排序：1.起泡排序      2. 快速排序
// 选择排序：1.简单选择排序、 2.树形选择排序      3.堆排序
// 归并排序：2-路归并。。。
// 基数排序：多关键字基数排序、链式基数排序


///// 这里只介绍：1.直接插入排序 2.起泡排序 3.简单选择排序


#include <stdio.h>

/**************************插入类排序*******************************/

/**直接插入排序
 * 从第一个元素开始，每趟增加一个参与排序的元素，在已经有序的序列中空出槽位，把新增的参与排序的元素放入这个槽位中，使之有序
 *
 * 具体的算法如下：
 * 第i趟排序只操作原来数组中的前i+1个元素,每趟操作之后整个序列的前i+1个元素有序
 * 再继续，则将新取的第i+2个元素插入到前i+1个元素中，使之有序
 *
 * 时间复杂度为O(n^2)
 */
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

/** 起泡排序 (交换排序算法中最简单的一种)
 *
 * 它的思路如下：
 * 通过比较和移动，每一趟排序将未排序的序列中的最大值(最小值)放到最后，未排序的序列中元素个数变为 n - 1
 * 继续进行前(n - 1)个元素的排序，一趟之后将这(n - 1)个元素中的最大值(最小值)放到这个序列的倒数第二个位置
 *....
 * 最后只剩下一个最小值(最大值)在序列的第一个位置
 */

/// 先冒泡最终的有序序列的低位
void BubbleSortLowFirst(int array[], int length) {
    /**
     * 一趟之后: {最小值, x, x, x, x}
     * 二趟之后: {最小值, 第二小值, x, x, x}
     * ....
     */
    for (int i = 0, exchange = true; i < length - 1 && exchange; i++) {
        exchange = false;
        for (int j = i + 1; j < length; j++) {
            if (array[j] < array[i]) {
                int temp = array[j];
                array[j] = array[i];
                array[i] = temp;
                exchange = true;
            }
        }
    }
}

/// 先冒泡最终的有序序列的高位
void BubbleSortHighFirst(int array[], int length) {
    
    /**
     * 一趟之后: {x, x, x, x, 最大值}
     * 二趟之后: {x, x, x, 第二大值, 最大值}
     * ....
     */
    for (int i = length - 1, exchange = true; i >= 1 && exchange; --i) {
        exchange = false;
        for (int j = 0; j < i; j++) {
            if (array[j+1] < array[j]) {
                int temp = array[j+1];
                array[j+1] = array[j];
                array[j] = temp;
                exchange = true;
            }
        }
    }
}


/***
 直接插入排序和起泡排序的比较：
 
 直接插入核心思想在于每趟使得有序序列的个数 + 1，操作的对象是序列
而起泡排序的核心思想在于每趟拿去一个最大值(最小值)，这样使得无序序列的个数 - 1，它操作的对象是元素
 
 因为操作对象的不同，产生这样几个结果：
 直接插入排序使用空出槽位填充的方式给有序序列做增量，几乎不涉及元素的交换，只是移位的操作，若用链表实现序列，只需两次修改后继和前驱操作即可完成。
 起泡排序中为了每趟拿到想要的值，做大量的交换，内存操作是非常频繁的，即使使用链表实现序列，修改前驱和后记的操作也是相当频繁的。
 
 *****/



/**
 * 起泡排序的效率分析
 若初始序列为“正序”序列，则只需进行一趟排序(算法必须使用exchange标记)，在排序过程中进行n-1次比较，且不移动记录；
 反之，若初始序列为“逆序”序列，则需进行n-1趟排序，需进行(n-1) + (n-2)+..+1 = n(n-1)/2次比较，并做等数量级的移动。因此总的时间复杂度为O(n^2)。
 */

///////// 交换类高级算法:快速排序

/**************************选择类排序*******************************/

/**
 简单选择排序的思路是：每趟在待排序的序列中选出一个最小的，与待排序列中的第一个值交换，
 不断通过上面的比较、记录索引、交换操作，逐渐构建有序序列。
 
 * 在这个过程中：
 * i趟之后前i个序列有序
 
 与冒泡的不同是，冒泡是在不断的比较和交换，而选择排序是在不断地比较并记录位置，一趟只进行一次交换
 */

///  返回每趟排序中最小值的位置
int SelectMin(int array[], int length, int start_index);

void SelectSort(int array[], int length) {
    for (int i = 0; i < length; i++) {
        int j = SelectMin(array, length, i);   // 从索引为i...length-1中找到最小的
        if (i != j) {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    
}

/// SelectMin的一种实现
int SelectMin(int array[], int length, int start_index) {
    int min_index = start_index;
    for (int i = start_index + 1; i < length; i++) {
        if (array[min_index] > array[i]) min_index = i;
    }
    return min_index;
}

/**
 性能分析：
 所需进行记录移动的操作次数较少，最小值为0，最大值为3（n - 1）
 无论记录的初始序列如何，所需进行的关键字比较次数相同，均为n(n-1)/2。因此总的时间复杂度为O(n^2)
 */

///////// 选择类高级算法:堆排序

/// test
int main() {
    #define ARRAY_SIZE (6)
    int array[] = {50, 10, 3, 8, 9, 11};

//    InsertSort(array, ARRAY_SIZE);
//    BinaryInsertSort(array, ARRAY_SIZE);
    
//    BubbleSortLowFirst(array, ARRAY_SIZE);
//    BubbleSortHighFirst(array, ARRAY_SIZE);
    
    SelectSort(array, ARRAY_SIZE);
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d  ", array[i]);
    }
    return 0;
}
