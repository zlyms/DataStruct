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
    TreeNode* data;      // ������
    struct LNode* next; // ָ����ָ����һ���ڵ�
} LNode;

typedef struct
{
    LNode* front; // ��ͷָ��
    LNode* rear;  // ��βָ��
} LQueue;          // ��ʽ���нṹ��

void IniLQueue(LQueue* LQ)
{
    LQ->front = NULL; // ��ʼ����ͷָ��
    LQ->rear = NULL;  // ��ʼ����βָ��
}

int isempty(LQueue* LQ)
{
    if (LQ->front == NULL) // �����ͷָ��Ϊ��
    {
        return 1; // ����Ϊ��
    }
    return 0; // ���зǿ�
}

int EnQueue(LQueue* LQ, TreeNode* e)
{
    LNode* p = (LNode*)malloc(sizeof(LNode)); // �����½ڵ���ڴ�ռ�
    if (p == NULL)
    {
        perror("EnQueue:"); // ���������Ϣ
        printf("����ռ�ʧ��\n"); // �����ʾ��Ϣ
        return 0; // ����ʧ��
    }
    if (LQ->front == NULL) // �������Ϊ��
    {
        LQ->front = p; // �½ڵ��Ϊ��ͷ�ڵ�
        LQ->rear = p;  // �½ڵ��Ϊ��β�ڵ�
    }
    p->data = e;    // ��Ԫ�ظ�ֵ���½ڵ��������
    p->next = NULL; // �½ڵ��nextָ���ÿ�
    LQ->rear->next = p; // ���½ڵ���ص���β�ڵ��
    LQ->rear = p;       // ���¶�βָ��Ϊ�½ڵ�

    return 1; // ���سɹ�
}

int deQueue(LQueue* LQ, TreeNode** e)
{
    if (isempty(LQ)) // �������Ϊ��
    {
        printf("�ӿ�\n"); // �����ʾ��Ϣ
        return 0; // ����ʧ��
    }
    LNode* p = LQ->front; // �����ͷ�ڵ�ĵ�ַ
    *e = p->data;          // ����ͷ�ڵ�����ݸ�ֵ��*e
    LQ->front = LQ->front->next; // ���¶�ͷָ��Ϊԭ��ͷ�ڵ����һ���ڵ�
    free(p);               // �ͷ�ԭ��ͷ�ڵ���ڴ�ռ�
    p = NULL;              // ��ԭ��ͷ�ڵ��ÿ�
    return 1;              // ���سɹ�
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

// ʵ�ֹ����������(�������)�����������ĺ���
void levelOrder(TreeRoot T, LQueue* LQ)
{
    if (T == NULL) // ���������Ϊ�գ���ֱ�ӷ���
    {
        return;
    }
    EnQueue(LQ, T); // �����ڵ����

    // ѭ���������У�ֱ������Ϊ��
    while (isempty(LQ) == 0)
    {
        deQueue(LQ, &T); // ���Ӳ����ʽڵ�
        printf("%d ", T->data.value); // ��ӡ�ڵ�ֵ

        // ����ǰ�ڵ���������
        if (T->LChild != NULL)
        {
            EnQueue(LQ, T->LChild);
        }

        // ����ǰ�ڵ���Һ������
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
