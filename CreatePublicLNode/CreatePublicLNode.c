#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#pragma warning(disable:4996)

// ��������ڵ����������Ϊ����
typedef int Elemtype;

// ��������ڵ�ṹ��
typedef struct LNode
{
	struct LNode* next; // ָ����һ���ڵ��ָ��
	Elemtype data; // �洢�ڵ����ݵı���
} LNode, * LinkList;

// ��ʼ����������Ϊָ������ͷ�ڵ��ָ���ָ��
void IniLinkList(LinkList* L)
{
	// �����ڴ������ͷ�ڵ�
	*L = (LNode*)malloc(sizeof(LNode));
	if (*L == NULL)
	{
		// �ڴ�����ʧ�ܵĴ�����
		printf("�ڴ�����ʧ��\n");
		perror("IniLinkList:");
		return;
	}
	(*L)->next = NULL; // ������ͷ�ڵ����һ���ڵ�ָ����Ϊ��
}

// �����������Ԫ��
int addElem(LinkList L, Elemtype e)
{
	// �����ڴ���½ڵ�
	LNode* p = (LNode*)malloc(sizeof(LNode));
	if (p == NULL)
	{
		// �ڴ�����ʧ�ܵĴ�����
		printf("�ڴ�����ʧ��\n");
		perror("addElem:");
		return 0;
	}
	p->data = e; // ���½ڵ������������Ϊ��������� e
	p->next = NULL; // ���½ڵ����һ���ڵ�ָ����Ϊ��

	LNode* temp = L;
	// �ҵ������β���ڵ�
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = p; // ���½ڵ����ӵ�����β��

	return 1;
}
int createPublicLNode(LinkList A, LinkList B, LinkList C)
{
	// ������� A ������ B �Ƿ�Ϊ��
	if (A->next == NULL || B->next == NULL)
	{
		return 0; // ����κ�һ������Ϊ�գ����޷��ҵ������ڵ㣬���� 0
	}

	LNode* rear, * p1, * p2; // ����ָ�� rear, p1, p2
	p1 = A->next; // p1 ָ������ A �ĵ�һ���ڵ�
	p2 = B->next; // p2 ָ������ B �ĵ�һ���ڵ�
	rear = C; // rear ָ������ C ���һ���ڵ�

	// A B��Ϊ��ʱ������ִ��ѭ��
	while (p1 != NULL && p2 != NULL)
	{
		// ��� p1 �� p2 ָ��Ľڵ�������ͬ
		if (p1->data == p2->data)
		{
			// ����һ���µĽڵ㲢��ֵΪ p1 ������
			LNode* ptr = (LNode*)malloc(sizeof(LNode));
			if (ptr == NULL)
			{
				printf("�ռ�����ʧ��\n");
				perror("createPublicLNode:");
				return 0; // ����ڴ����ʧ�ܣ��򷵻� 0
			}
			ptr->data = p1->data;

			// ���½ڵ����ӵ����� C ��β��
			rear->next = ptr;
			rear = ptr;

			// �ƶ� p1 �� p2 ����һ���ڵ�
			p1 = p1->next;
			p2 = p2->next;
		}
		//����С�����ߣ������ظ��Ƚ�
		else if (p1->data - p2->data < 0)
		{
			p1 = p1->next; // �ƶ� p1 ����һ���ڵ�
		}
		else
		{
			p2 = p2->next; // �ƶ� p2 ����һ���ڵ�
		}
	}
	return 1; // ����ִ�гɹ������� 1
}

int main()
{
	LinkList L1;
	LinkList L2;
	LinkList L3;
	IniLinkList(&L1); // ��ʼ������
	IniLinkList(&L2); // ��ʼ������
	IniLinkList(&L3); // ��ʼ������
	addElem(L1, 1);
	addElem(L1, 3);
	addElem(L1, 5);
	addElem(L1, 7);

	addElem(L2, 2);
	addElem(L2, 4);
	addElem(L2, 6);
	addElem(L2, 7);
	createPublicLNode(L1,L2,L3);
	return 0;
}
