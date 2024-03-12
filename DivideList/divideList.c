#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#pragma warning(disable:4996)

typedef char Elemtype[3];

typedef struct LNode
{
	struct LNode* next;
	Elemtype data;
}LNode, * LinkList;

void IniLinkList(LinkList* L)
{
	*L = (LNode*)malloc(sizeof(LNode));
	if (*L == NULL)
	{
		printf("�ڴ�����ʧ��\n");
		perror("IniLinkList:");
		return;
	}
	(*L)->next = NULL;
}

int addElem(LinkList L, Elemtype e)
{
	LNode* p = (LNode*)malloc(sizeof(LNode));
	if (p == NULL)
	{
		printf("�ڴ�����ʧ��\n");
		perror("addElem:");
		return 0;
	}
	strcpy(p->data, e);
	p->next = NULL;

	LNode* temp = L;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = p;

	return 1;
}
//����{a1,b1,a2,b2,a3,b3,...an,bn}��ֳ�������,��L1����{bn...b3,b2,b1}����L2����{a1,a2,a3...an}
int divideList(LinkList L1, LinkList L2)
{
	if (L1 == NULL || L2 == NULL)
	{
		return 0;
	}

	LNode* temp ;//temp��¼����ָ��s����һλ��
	LNode* rear = L2;//rearָ��L2��β�������Ԫ��
	LNode* s = L1->next;//sɨ��Դ��

	while (s != NULL)
	{
		if (s->data[0] == 'a')//β������
		{
			rear->next = s;
			rear = s;
			s = s->next;
		}
		else if (s->data[0] == 'b')//ͷ������
		{
			temp = s->next;//��¼��һλ�ã���ֹ����֮���ڴ�й©
			s->next = L1->next;//����
			L1->next = s;
			s = temp;
		}
		
	}
	rear->next = NULL;
	return 1;
}

int main()
{
	LinkList L1;
	LinkList L2;
	IniLinkList(&L1);
	IniLinkList(&L2);

	addElem(L1, "a1");
	addElem(L1, "a2");
	addElem(L1, "b1");
	addElem(L1, "b2");
	addElem(L1, "a3");
	addElem(L1, "b3");
	divideList(L1, L2);

	return 0;
}
