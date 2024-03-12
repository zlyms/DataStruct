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

// ɾ���������ظ���Ԫ��
int removeExcessElem(LinkList L)
{
	LNode* p = L->next->next; // p ָ������ĵڶ����ڵ�
	LNode* q = L->next; // q ָ������ĵ�һ���ڵ�
	if (p == NULL)
	{
		// ������û�нڵ��ֻ��һ���ڵ㣬���账��
		return 0;
	}
	while (p != NULL)
	{
		if (p->data == q->data)
		{
			// �����ǰ�ڵ��������ǰһ���ڵ��������ͬ����ɾ����ǰ�ڵ�
			q->next = p->next;
			free(p); // �ͷŵ�ǰ�ڵ���ڴ�
			p = NULL;
			p = q->next; // �ƶ� p ����һ���ڵ�
		}
		else
		{
			// �����ǰ�ڵ��������ǰһ���ڵ�����ݲ�ͬ���������������
			q = q->next;
			p = p->next;
		}
	}
	return 1;
}

int main()
{
	LinkList L1;
	IniLinkList(&L1); // ��ʼ������

	// �����������Ԫ��
	addElem(L1, 1);
	addElem(L1, 2);
	addElem(L1, 2);
	addElem(L1, 3);
	addElem(L1, 3);
	addElem(L1, 3);

	// ɾ���������ظ���Ԫ��
	removeExcessElem(L1);

	return 0;
}
