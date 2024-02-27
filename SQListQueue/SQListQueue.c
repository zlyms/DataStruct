#include <stdio.h>

#define CAPACITY 10 // 定义队列容量为10
typedef int Elemtype; // 定义元素类型为整数
typedef struct
{
    Elemtype data[CAPACITY]; // 队列数据数组
    int rear, front; // 队列尾部和头部指针
} SQqueue; // 定义顺序队列结构体

void IniSQquee(SQqueue* sq)
{
    sq->front = 0; // 初始化队列头指针
    sq->rear = 0; // 初始化队列尾指针
}

int EnQueue(SQqueue* sq, Elemtype e)
{
    if ((sq->rear + 1) % CAPACITY == sq->front) // 如果队列已满
    {
        printf("队列已满\n"); // 输出提示信息
        return 0; // 返回失败
    }
    sq->data[sq->rear] = e; // 将元素插入队尾
    sq->rear = (sq->rear + 1) % CAPACITY; // 更新队尾指针
    return 1; // 返回成功
}

int isempty(SQqueue* sq)
{
    if (sq->front == sq->rear) // 如果队列头尾指针相等
    {
        return 1; // 队列为空
    }
    else
    {
        return 0; // 队列非空
    }
}

int deQueue(SQqueue* sq, int* x)
{
    if (isempty(sq)) // 如果队列为空
    {
        printf("队空\n"); // 输出提示信息
        return 0; // 返回失败
    }
    *x = sq->data[sq->front]; // 读取队头元素
    sq->front = (sq->front + 1) % CAPACITY; // 更新队头指针
    return 1; // 返回成功
}

int Gethead(SQqueue* sq, int* x)
{
    if (isempty(sq)) // 如果队列为空
    {
        printf("队空\n"); // 输出提示信息
        return 0; // 返回失败
    }
    *x = sq->data[sq->front]; // 读取队头元素
    return 1; // 返回成功
}

int main()
{
    SQqueue sq; // 声明顺序队列变量
    int x; // 定义整型变量x
    IniSQquee(&sq); // 初始化队列
    EnQueue(&sq, 5); // 入队元素5
    EnQueue(&sq, 3); // 入队元素3
    EnQueue(&sq, 3); // 入队元素3
    EnQueue(&sq, 3); // 入队元素3
    EnQueue(&sq, 3); // 入队元素3
    EnQueue(&sq, 3); // 入队元素3
    EnQueue(&sq, 3); // 入队元素3
    EnQueue(&sq, 3); // 入队元素3
    EnQueue(&sq, 3); // 入队元素3
    EnQueue(&sq, 3); // 入队元素3
    //deQueue(&sq, &x); // 出队，并将出队元素存储在x中
    Gethead(&sq, &x); // 获取队头元素，并将其存储在x中
    printf("%d\n", x); // 输出队头元素
    return 0; // 返回成功
}
