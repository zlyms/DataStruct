#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable: 4996)

typedef struct ElemType
{
    int value;
} ElemType;

typedef struct TreeNode
{
    ElemType data;
    struct TreeNode* LChild;
    struct TreeNode* RChild;
} TreeNode, * TreeRoot;


typedef struct LNode
{
    TreeNode* data;      // 数据域
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

int EnQueue(LQueue* LQ, TreeNode* e)
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

int deQueue(LQueue* LQ, TreeNode** e)
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

void IniTree(TreeRoot* T)
{
    *T = NULL;
}

int empityTree(TreeRoot T)
{
    if (T == NULL)
    {
        return 0;
    }
    return 1;
}

void creatBinTree(TreeRoot* T, int sz)
{
    if (*T != NULL || sz <= 0)
    {
        return;
    }
    int e = 0;
    int temp = sz;
    scanf_s("%d", &e);
    TreeNode* p = (TreeNode*)malloc(sizeof(TreeNode));
    if (p == NULL)
    {
        perror("creatBinTree:");
        return;
    }
    p->data.value = e;
    p->LChild = p->RChild = NULL;
    *T = p;
    creatBinTree(&((*T)->LChild), --sz);
    sz = temp;
    creatBinTree(&((*T)->RChild), --sz);
}

void locate(TreeRoot T, int e, TreeNode** x)
{
    if (T == NULL)
    {
        return;
    }
    if (T->data.value == e)
    {
        *x = T;
    }
    locate(T->LChild, e, x);
    locate(T->RChild, e, x);
}

int addchild(TreeRoot T, TreeNode* x, TreeRoot T1, int b)
{
    if (b == 0)
    {
        x->LChild = T1;
    }
    else if (b == 1)
    {
        x->RChild = T1;
    }
    return 1;
}

void postorderdelete(TreeRoot* T)
{
    if (*T == NULL)
    {
        return;
    }
    postorderdelete(&((*T)->LChild));
    postorderdelete(&((*T)->RChild));
    free((*T));
    *T = NULL;
}

void deleteChild(TreeRoot T, TreeNode* x, int b)
{
    if (T == NULL)
    {
        return;
    }
    TreeNode* p = NULL;
    if (b == 0)
    {
        p = x->LChild;
    }
    else if (b == 1)
    {
        p = x->RChild;
    }
    postorderdelete(&p);
}

// 实现广度优先搜索(层序遍历)遍历二叉树的函数
void levelOrder(TreeRoot T, LQueue* LQ)
{
    if (T == NULL) // 如果二叉树为空，则直接返回
    {
        return;
    }
    EnQueue(LQ, T); // 将根节点入队

    // 循环遍历队列，直到队列为空
    while (isempty(LQ) == 0)
    {
        deQueue(LQ, &T); // 出队并访问节点
        printf("%d ", T->data.value); // 打印节点值

        // 将当前节点的左孩子入队
        if (T->LChild != NULL)
        {
            EnQueue(LQ, T->LChild);
        }

        // 将当前节点的右孩子入队
        if (T->RChild != NULL)
        {
            EnQueue(LQ, T->RChild);
        }
    }
}


int main()
{
    TreeRoot T;
    LQueue lq;
    IniLQueue(&lq);
    IniTree(&T);
    creatBinTree(&T, 3);
    levelOrder(T, &lq);
    return 0;
}
