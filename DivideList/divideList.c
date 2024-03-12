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
		printf("内存申请失败\n");
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
		printf("内存申请失败\n");
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
//将表{a1,b1,a2,b2,a3,b3,...an,bn}拆分成两个表,表L1逆序{bn...b3,b2,b1}，表L2正序{a1,a2,a3...an}
int divideList(LinkList L1, LinkList L2)
{
	if (L1 == NULL || L2 == NULL)
	{
		return 0;
	}

	LNode* temp ;//temp记录工作指针s的下一位置
	LNode* rear = L2;//rear指向L2表尾方便添加元素
	LNode* s = L1->next;//s扫描源表

	while (s != NULL)
	{
		if (s->data[0] == 'a')//尾插正序
		{
			rear->next = s;
			rear = s;
			s = s->next;
		}
		else if (s->data[0] == 'b')//头插逆序
		{
			temp = s->next;//记录下一位置，防止断链之后内存泄漏
			s->next = L1->next;//断链
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
