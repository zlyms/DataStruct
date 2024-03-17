#include<stdio.h> // 包含标准输入输出库

#define MAXSIZE 100 // 定义树节点的最大数量
#define CAPACITY 10 // 定义栈的最大容量

typedef int Elemtype; // 定义树节点和栈中元素的类型为整数
typedef struct stack // 定义栈的结构体
{
    Elemtype data[CAPACITY]; // 数据数组
    int top; // 栈顶指针
}SQLstack;

typedef struct // 定义树节点的结构体
{
    Elemtype data; // 数据
    int isempity; // 是否为空
}TreeNode[MAXSIZE];

void IniStack(SQLstack* s) // 初始化栈
{
    s->top = -1; // 栈顶指针设为-1，表示栈为空
}

int Puch(SQLstack* s, Elemtype e) // 元素入栈
{
    if (s->top == CAPACITY - 1) // 如果栈已满
    {
        printf("栈区已满\n");
        return 0; // 入栈失败
    }
    s->data[++(s->top)] = e; // 栈顶指针加1，元素入栈
    return 1; // 入栈成功
}

Elemtype Pop(SQLstack* s) // 元素出栈
{
    if (s->top == -1) // 如果栈为空
    {
        printf("空栈\n");
        return 0; // 出栈失败
    }
    Elemtype e = s->data[s->top--]; // 获取栈顶元素，栈顶指针减1
    return e; // 返回出栈的元素
}

Elemtype Getelement(SQLstack* s) // 获取栈顶元素
{
    if (s->top == -1) // 如果栈为空
    {
        printf("空栈\n");
        return 0; // 返回0
    }
    return s->data[s->top]; // 返回栈顶元素
}

void IniTree(TreeNode T)  // 初始化二叉树
{
    if (T == NULL) // 如果二叉树为空
    {
        return; // 返回
    }
    for (int i = 0; i < MAXSIZE; i++) // 遍历二叉树节点数组
    {
        T[i].isempity = 1; // 将节点的isempity置为1，表示为空
    }
}

int addElem(TreeNode T, Elemtype e) // 添加元素到二叉树中
{
    for (int i = 1; i < MAXSIZE; i++) // 遍历二叉树节点数组
    {
        if (T[i].isempity) // 如果当前节点为空
        {
            T[i].data = e; // 将数据e添加到当前节点
            T[i].isempity = 0; // 将当前节点的isempity置为0，表示非空
            break; // 结束循环
        }
    }
    return 1; // 添加成功
}

int preorderVist(TreeNode T, SQLstack* S) // 二叉树的前序遍历
{
    Elemtype TLNode = 1; // 定义树节点
    Puch(S, T[1].data); // 根节点入栈
    while (T[TLNode].isempity != 1) // 循环直到遍历完树
    {
        TLNode = Pop(S); // 弹出子树的根并方便进行左右节点的访问
        if (TLNode < 1) // 如果栈顶元素小于1
        {
            return 1; // 结束遍历
        }
        printf("%d", TLNode); // 访问子树根节点

        if (T[2 * TLNode + 1].isempity == 0) // 如果右子节点不为空
        {
            Puch(S, T[2 * TLNode + 1].data); // 右子节点入栈
        }
        if (T[2 * TLNode].isempity == 0) // 如果左子节点不为空
        {
            Puch(S, T[2 * TLNode].data); // 左子节点入栈
        }
    }
    return 1; // 遍历完成
}

int main() // 主函数
{
    TreeNode T; // 声明二叉树节点数组
    SQLstack S; // 声明栈
    IniStack(&S); // 初始化栈
    addElem(T, 1); // 向二叉树中添加元素
    addElem(T, 2);
    addElem(T, 3);
    addElem(T, 4);
    addElem(T, 5);
    addElem(T, 6);
    preorderVist(T, &S); // 进行前序遍历
    return 0; // 返回0，表示程序正常结束
}
