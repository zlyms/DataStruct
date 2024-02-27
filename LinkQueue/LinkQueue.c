#include<stdio.h>
#include<stdlib.h>

typedef int Elemtype;

typedef struct LNode
{
    Elemtype data;      // ������
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

int EnQueue(LQueue* LQ, Elemtype e)
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

int deQueue(LQueue* LQ, Elemtype* e)
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
//int EnQueue(LQueue* LQ, Elemtype e)
//{
//		LNode* p = (LNode*)malloc(sizeof(LNode));
//		if (p == NULL) 
//		{
//			perror("EnQueue:");
//			printf("����ռ�ʧ��\n");
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
    if (isempty(LQ)) // �������Ϊ��
    {
        printf("�ӿ�\n"); // �����ʾ��Ϣ
        return 0; // ����ʧ��
    }
    *e = LQ->front->data; // ��ȡ��ͷ�ڵ������
    return 1;              // ���سɹ�
}

int main()
{
    LQueue LQ;    // ������ʽ���б���
    IniLQueue(&LQ); // ��ʼ������
    Elemtype x;   // �������ͱ���x
    EnQueue(&LQ, 5); // ���Ԫ��5
    EnQueue(&LQ, 3); // ���Ԫ��3
    EnQueue(&LQ, 3); // ���Ԫ��3
    EnQueue(&LQ, 3); // ���Ԫ��3
    deQueue(&LQ, &x); // ���ӣ���������Ԫ�ش洢��x��
    GetElem(&LQ, &x); // ��ȡ��ͷԪ�أ�������洢��x��
    printf("%d\n", x); // �����ͷԪ��
    return 0; // ���سɹ�
}
