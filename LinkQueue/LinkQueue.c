#include<stdio.h>
#include<stdlib.h>

typedef int Elemtype;

typedef struct LNode
{
    Elemtype data;      // 数据域
    struct LNode* next; // 指针域，指向下一个节点
} LNode;

typedef struct
{
    LNode* front; // 队头指针
    LNode* rear;  // 队尾指针
} LQueue;          // 链式队列结构体

void IniLQueue(LQueue* LQ)
{
    LQ->front = NULL; // 初始化队头指针
    LQ->rear = NULL;  // 初始化队尾指针
}

int isempty(LQueue* LQ)
{
    if (LQ->front == NULL) // 如果队头指针为空
    {
        return 1; // 队列为空
    }
    return 0; // 队列非空
}

int EnQueue(LQueue* LQ, Elemtype e)
{
    LNode* p = (LNode*)malloc(sizeof(LNode)); // 分配新节点的内存空间
    if (p == NULL)
    {
        perror("EnQueue:"); // 输出错误信息
        printf("申请空间失败\n"); // 输出提示信息
        return 0; // 返回失败
    }
    if (LQ->front == NULL) // 如果队列为空
    {
        LQ->front = p; // 新节点成为队头节点
        LQ->rear = p;  // 新节点成为队尾节点
    }
    p->data = e;    // 将元素赋值给新节点的数据域
    p->next = NULL; // 新节点的next指针置空
    LQ->rear->next = p; // 将新节点挂载到队尾节点后
    LQ->rear = p;       // 更新队尾指针为新节点

    return 1; // 返回成功
}

int deQueue(LQueue* LQ, Elemtype* e)
{
    if (isempty(LQ)) // 如果队列为空
    {
        printf("队空\n"); // 输出提示信息
        return 0; // 返回失败
    }
    LNode* p = LQ->front; // 保存队头节点的地址
    *e = p->data;          // 将队头节点的数据赋值给*e
    LQ->front = LQ->front->next; // 更新队头指针为原队头节点的下一个节点
    free(p);               // 释放原队头节点的内存空间
    p = NULL;              // 将原队头节点置空
    return 1;              // 返回成功
}
//int EnQueue(LQueue* LQ, Elemtype e)
//{
//		LNode* p = (LNode*)malloc(sizeof(LNode));
//		if (p == NULL) 
//		{
//			perror("EnQueue:");
//			printf("申请空间失败\n");
//			return 0;
//		}
//		if (LQ->front == NULL) 
//		{
//			LQ->front = p;
//			p->next = NULL;
//			LQ->rear = p;
//		}
//		p->data = e;
//		p->next = LQ->rear->next;
//		LQ->rear->next = p;
//		LQ->rear = p;
//
//		return 0;
//}

int GetElem(LQueue* LQ, Elemtype* e)
{
    if (isempty(LQ)) // 如果队列为空
    {
        printf("队空\n"); // 输出提示信息
        return 0; // 返回失败
    }
    *e = LQ->front->data; // 获取队头节点的数据
    return 1;              // 返回成功
}

int main()
{
    LQueue LQ;    // 声明链式队列变量
    IniLQueue(&LQ); // 初始化队列
    Elemtype x;   // 定义整型变量x
    EnQueue(&LQ, 5); // 入队元素5
    EnQueue(&LQ, 3); // 入队元素3
    EnQueue(&LQ, 3); // 入队元素3
    EnQueue(&LQ, 3); // 入队元素3
    deQueue(&LQ, &x); // 出队，并将出队元素存储在x中
    GetElem(&LQ, &x); // 获取队头元素，并将其存储在x中
    printf("%d\n", x); // 输出队头元素
    return 0; // 返回成功
}
