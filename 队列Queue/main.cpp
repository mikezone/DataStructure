// 链队列LinkQueue的实现
//


#include <stdlib.h>
#include <stdio.h>


typedef int Status;
typedef int Index;
#define ERROR -1
#define OVERFLOW -2 //
#define RangeException -3 // 数组越界
#define OK 0



#define MAXSIZE 100
typedef int QElemType;

typedef struct QNode {
    QElemType data;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;


Status InitQueue(LinkQueue &Q)
{//构造一个空队列
    
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if (!Q.front) exit(OVERFLOW);
    Q.front->next = NULL;
    return OK;
}

Status DestroyQueue(LinkQueue &Q)
{//销毁队列Q
    
    while(Q.front)
    {
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return OK;
}

Status ClearQueue(LinkQueue &Q)
{//将Q清为空
    
    QueuePtr p,q;
    Q.rear = Q.front;
    p = Q.front->next;
    Q.front->next = NULL;
    while(p)
    {
        q = p;
        p=p->next;
        free(q);
    }
    return OK;
}

bool QueueEmpty(LinkQueue &Q)
{//若Q为空队列，则返回TRUE，否则返回FALSE
    
    if(Q.front == Q.rear)
        return true;
    return false;
}

int QueueLength(LinkQueue &Q)
{//求队列的长度
    
    int i=0;
    QueuePtr p;
    p = Q.front;
    while(Q.rear !=p)
    {
        i++;
        p=p->next;
    }
    return i;
}

Status GetHead(LinkQueue &Q,QElemType &e)
{//若队列不空，用e返回Q的队头元素，并返回OK ，否则返回ERROR;
    
    QueuePtr p;
    if(Q.front == Q.rear)
        return ERROR;
    p=Q.front->next;
    e = p->data;
    return OK;
}

Status EnQueue(LinkQueue &Q,QElemType e)
{//插入元素e为Q的新的队尾元素
    
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if(!p) exit(OVERFLOW);
    p->data = e;
    p->next = NULL;
    Q.rear->next = p; // 与尾插法建表类似
    Q.rear = p;
    return OK;
}

Status DeQueue(LinkQueue &Q,QElemType &e)
{//若队列不空，删除Q的对头元素，用e返回其值，并返回OK，否则返回ERROR
    if(Q.front == Q.rear) return ERROR;
    QueuePtr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if(Q.rear == p) Q.rear = Q.front;
    free(p);
    return OK;
}

// 遍历
void visit(QElemType e) {
    printf("%d\n", e);
}

Status QueueTraverse(LinkQueue &Q, void(*visit)(QElemType))
{// 从队头到队尾依次对队列Q中每个元素调用函数vi().
    
    QueuePtr p = Q.front->next;
    while(p)
    {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

int main() {
    LinkQueue Q;
    InitQueue(Q);
    
    EnQueue(Q, 10);
    EnQueue(Q, 20);
    QueueTraverse(Q, visit);
    
    QElemType e;
    DeQueue(Q, e);
    printf("DeQueue----%d\n",e);
    QueueTraverse(Q, visit);
    
    
    return 0;
}


