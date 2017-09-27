//
//  main.cpp
//  堆排序HeapSort
//
//  Created by Mike on 2017/9/25.
//  Copyright © 2017年 Mike. All rights reserved.
//

#include <iostream>
using namespace std;
void HeapAdjustFTTB(int *array, int array_length, int adjust_index);

/**
 选择排序的主要操作是进行关键字间的比较，因此改进简单的选择排序应在如何减少比较的次数考虑。显然，在n个关键字中选出最小值，至少要进行n-1此比较，然而，**继续在剩余的n-1个关键字中选择次小值就非一定要进行n-2次比较，若能利用前n-1次比较所得信息，则可减少以后各趟选择排序中所用的比较次数**。
 实际上，体育比赛中的锦标赛变是一种选择排序。例如，在8个运动员中决出前3名之多需要11场比赛，而不是7+6+5=18场(它的前提是，若乙胜丙，甲胜乙，则认为甲必能胜丙)。如下图：
 ①如图a，先进行7场比赛，决出冠军BAO
 ②按照传递关系，亚军只能产生于分别在决赛、半决赛、第一轮比赛中败给冠军的选手。由此，如图b，在经过 CHA和LIU、CHA和DIAO的两场比赛之后，选出了亚军CHA。
 ③同理，选拔季军的比赛只要在ZHAO、LIU、DIAO这3个选手之间进行即可。如图c，结果比赛，选出DIAO。
 
 按照这种锦标赛的思想可导出树形选择排序。
 
 树形选择排序（Tree Selection Sort）,又称锦标赛排序(Tournament Sort),是一种按照锦标赛的思想进行选择排序的方法。首先对n个记录进行两两比较，然后在其中ceil(n/2)个较小者之间再进行两两比较，如此重复，直至选出最小的关键字的记录为止。
 这个过程可用一棵有n个叶子结点的**完全二叉树**表示。例如，
 ①下图a中的二叉树表示从8个值中选出最小值的过程。8个叶子结点中依次存放排序之前的8个值，每个非终端节点中的值军等于其左、右孩子中较小的值。
 ②在输出最小的值(也就是根节点的值)之后，仅需将叶子结点中最小值13改为一个无限大的值，然后从该叶子结点开始，再与其兄弟比较，不断修改向根结点路径上的值，则又在根结点产生了一个最小值27.
 ③同理，可依次选出从小到达的所有值。
 
 由于含有n个叶子几点的完全二叉树的深度为ceil(log2(n))+1,则在树形选择排序中，除了最小值之外，每选择一个次小值仅需进行ceil(log2(n))次比较因此它的时间复杂度为O(nlog(n))。但是这种排序方法有**辅助存储空间较多**(这个树形结构上，除了叶子结点其他结点都需要辅助空间)、**最大值进行多余比较**等缺点。为了弥补，威洛姆斯(J.willioms)在1964年提出了另一种形式的选择排序————堆排序。
 
 堆排序：
 只需要一个记录大小的辅助空间，每个待排序列的记录值仅占有一个存储空间。
 堆的定义如下：n个元素的序列{k1,k2,...,kn}当且仅当满足下列关系时，称之为堆。
 ki <= k(2i) 且 ki <= k(2i + 1) ，称之为小根堆，或者：
 ki >= k(2i) 且 ki >= k(2i + 1) ，称之为小根堆
 容易看出，若将这个数据序列每个元素对应到一个完全二叉树中，那么他就是这样一棵完全二叉树：
 小根堆：所有的非终端节点的值均<=其孩子节点的值
 大根堆：所有的非终端节点的值均>=其孩子节点的值.
 那么依照递归关系可得出这样的结论：
 若序列是小根堆，则对应的树结构中的根结点是整个序列的最小值；
 若序列是大根堆，则对应的树结构中的根结点是整个序列的最大值。
 那么我们就有了一个堆排序的思路：
 ⑴将序列构建为一个堆(只要使相应下标对应的数值满足堆定义即可)
 ⑵假设排序结果为从小到大，可以有两种方法进行：
 方法①：调整的堆为小根堆，从堆中弹出堆顶元素，即最小值，将这个值放到结果集中的第一个位置；
 调整堆结构，再次弹出堆顶放到结果集的第二个位置
 ....
 方法①：调整的堆为大根堆，从堆中弹出堆顶元素，即最大值，将这个值放到结果集中的倒数第一个位置；
 调整堆结构，再次弹出堆顶放到结果集的倒数第二个位置
 ....
 ⑶反复经过上面的操作，直到堆为空，结果集填满。
 
 那么我们现在有两个问题：
 ①如何将序列调整为堆，
 ②如何在弹出一个新的堆顶之后调整堆。
 
 如果指定调整一个序列中的一个位置，使其子节点都满足堆的定义，那么只要不断和子节点的值比较并交换即可完成；
 对于整个序列的调整依然可以使用整个思路，对序列中前ceil(log(n))+1个节点(也就是树中所有的非终端节点)进行调整，那么得到的整个序列也就是堆了。这样第一个问题就变成了**调整前ceil(log(n))+1个节点**的过程。
 对于第二个问题：弹出堆顶之后，树形结构变成了森林，此时我们可以将序列的最后一个元素充当暂时的堆顶，然后调整这个节点就产生新的堆。
 
 如图a,完全二叉树表示一个有8个元素的无序序列：
 {49， 38， 65， 97， 76， 13， 27， *49}，将它调整为小根堆
 ①从终端结点向非终端节点看，需要筛选的第一个非终端节点为97，筛选从97开始，由于97>孩子*49则交换，变成图b
 ②同理，对下一个非终端结点65进行筛选，调整结果为图c
 ③然后看结点38，因为38<左孩子*49，且38<右孩子76,所以38不动
 ④最后筛选根节点49，因为49<左孩子38且49<右孩子13，并且左孩子38<右孩子13，所以49跟13交换，继续进行49应该与27交换，整个过程就是图d变成图e的过程。
 
 这样一个序列就调整为了堆结构，具体算法如下
 
 */

//void HeapAdjustFTTB(int *array, int array_length, int adjust_index) {
//    int value = array[adjust_index];
//    for (int i = 2 * adjust_index + 1; i < array_length; i = i*2 + 1) {
//        if (i < array_length - 1 && array[i] > array[i+1]) {
//            i++; // 右孩子比左孩子小,则将i加1, 用i来记录两者最小值的index
//        }
//        if (value <= array[i]) { // 如果比两个孩子中最大值都小
//            break;
//        }
//        array[adjust_index] = array[i]; // 将最小孩子上移，这样i位置的槽位就空出了，此时应不急于赋上value的值，而是继续向下调整(继续循环)，找出最下层的位置
//        adjust_index = i; // 将要调整的位置下移到有较小值的孩子的位置
//    }
//    array[adjust_index] = value;
//}

void Heapify(int *array, int array_length) {
    for (int i = array_length / 2; i >= 0; --i) {
        HeapAdjustFTTB(array, array_length, i);
    }
}

/**
 我们再看问题2：弹出堆顶，再调整堆
 此时的堆顶刚好在堆序列中是第一个元素，我们可以将第一个元素剔除，然后对剩下的元素，也就是{第二个,第三个元素,....,最后一个元素}进行堆调整：
 剔除第一个元素后，剩下的属性结构是森林，为了保持完全二叉树的结构，将最后一个元素放到第一个元素的位置，然后再对这个刚放上去的暂时的根元素进行自上而下的调整。
 整个如下图：
 ①在a中剔除了堆顶13，用最后一个元素97顶替，变成了图b
 ②对图b中的堆顶97调整，变成了图c，27成为了新堆顶
 ③剔除27， 用堆中最后一个元素97顶替新堆顶，调整之后变成了图d.....
 
 这个过程的代码如下：
 */

void Repeat_PopTopThenAdjust(int *array, int array_length) {
    for (int i = array_length - 1; i > 0; i--) {
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        HeapAdjustFTTB(array, i - 1, 0);
    }
}

/**
 通过以上的分析和代码可知，当我们不断进行剔除堆顶，并将剔除的元素放到序列后面，然后调整这三个操作时，每组操作之后，有序序列个数+1，堆中的元素-1
 {堆：13 38 27 49 76 65 49 97}
 {堆：27 38 65 49 76 97 49 | 13}
 {堆：38 49 65 49 76 97 | 27 13}
 {堆：49 49 65 97 76 | 38 27 13}
 {堆：49 76 65 97 | 49 38 27 13}
 {堆：76 97 65 | 49 49 38 27 13}
 {堆：65 97 | 76 49 49 38 27 13}
 {堆：97 | 65 76 49 49 38 27 13}
 堆变空 {97 65 76 49 49 38 27 13}
 
 此时排序已经完成，将数组空间分割成两部分，一部分仍符合堆结构，一部分存放排序序列，这样丝毫没有再使用额外的空间。不过可惜的是，因为使用的是小根堆，所以最先弹出最小元素，以至于最终结果是递减的。若想结果为递增，使用大根堆即可。可对照写出大根堆的算法：
 */


/// FTTB:from top to bottom
void HeapAdjustFTTB(int *array, int array_length, int adjust_index) {
    int value = array[adjust_index];
    for (int i = 2 * adjust_index + 1; i < array_length; i = i*2 + 1) {
        if (i < array_length - 1 && array[i] < array[i+1]) {
            i++; // 用i记录最大的孩子
        }
        if (value >= array[i]) { // 如果比两个孩子中最大值都大，则结束
            break;
        }
        array[adjust_index] = array[i];
        adjust_index = i;
    }
    array[adjust_index] = value;
}

/*
 测试一下完整的算法
 */

/// 使用大根堆排序
void _HeapSort(int *array, int array_length) {
    
    Heapify(array, array_length);
    
    // Repeat_PopTopThenAdjust
    for (int i = array_length - 1; i > 0; i--) {
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        
        HeapAdjustFTTB(array, i - 1, 0);
    }
}

////////////////////////////////////////////// 扩展
/**
 有时候会有这样的需求
 ①不断向堆结构中增加新的元素，使一个堆结构仍然是堆
 ②将堆结构抽取为单独数据类型，而不是在堆排序过程中，让堆和已排序的序列共享一个数组。
 
 这其实可以看成是一个大问题：实现堆结构，而需求①中的解决其实就是如何完成堆的push操作。
 堆结构在很多语言有广泛的使用，如Python的heapq模块，这里依据使用C语言实现，不过使用了少量的C++特性(如：引用)。
 用一个可以动态分配的数组来实现堆结构，它有以下基本操作：
 ①本来不是堆结构的数组，可以使用heapify调整为堆（前面已经实现，这里不再介绍）
 ②push操作，向堆中增加元素，需要动态调整数组长度，增加元素后调整，仍然为堆结构
 ③pop操作，弹出堆顶元素，需要动态调整数组长度，弹出后调整，使之仍然为堆结构
 ④配合以上方法完成一个对数组排序的过程。
 
 以下是一些我的实现：
 
 */


/// pop操作相当简单，将堆结构第一个元素弹出并作为最后的返回值，暂时用最后一个元素代替堆顶，自顶向下调整堆结构，调整之后收缩堆结构的长度，使长度-1.
int HeapPop(int *&ptr, int array_length) {
    int returnValue = ptr[0];
    ptr[0] = ptr[array_length - 1];
    ptr = (int *)realloc(ptr, sizeof(int) * (array_length - 1));
    HeapAdjustFTTB(ptr, array_length, 0);
    return returnValue;
}

/// push操作要首先对堆结构长度扩充，在最后填入新增元素，调整的做法是：从新增元素自底向上调整，直到产生合适的堆顶

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


/// 这是一个使用堆结构进行排序的方法，只是一个演示，实际中并不会这样做，因为在拷贝待排序列到堆结构中太占用内存。
void HeapSort(int *array, int array_length) {
    int *heap = (int *)malloc(sizeof(int) * array_length);
    memcpy(heap, array, sizeof(int) * array_length);
    
    Heapify(heap, array_length);
    
    for (int i = array_length; i > 0; i --) {
        int max = HeapPop(heap, i); // 注意这里的i是heap的长度
        array[i-1] = max; // 这里的i-1是最终排序结果的index
    }
}

//////////////////////////////////////////////

//========排序后：============
//13 27 38 49 49 65 76 97
//
//int main(int argc, const char * argv[]) {
//#define ARRAY_SIZE (8)
//    int array[] = {49, 38, 65, 97, 76, 13, 27, 49};
//    
//    _HeapSort(array, ARRAY_SIZE);
//    cout<<"========排序后：============"<<endl;
//    for (int i = 0; i < ARRAY_SIZE; i++) {
//        cout<<array[i]<<" ";
//    }
//}

int main(int argc, const char * argv[]) {
    #define ARRAY_SIZE (8)
    int array[] = {49, 38, 65, 97, 76, 13, 27, 49};
    
    
    // 测试 Heapify HeapPush HeapPop
    int *heap = (int *)malloc(sizeof(int) * ARRAY_SIZE);
    memcpy(heap, array, sizeof(int) * ARRAY_SIZE);
    Heapify(heap, ARRAY_SIZE);
    
    HeapPush(heap, ARRAY_SIZE, 17);

    int size = ARRAY_SIZE + 1;
    while (size) {
        cout<<HeapPop(heap, size--)<<" ";
    }
    
    // 测试排序
    HeapSort(array, ARRAY_SIZE);
    cout<<endl<<"========排序后：============"<<endl;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        cout<<array[i]<<" ";
    }
    
    return 0;
}
