#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

// ��������ڵ�ṹ��
typedef struct LNode {
	ElemType data;          // ������
	struct LNode* next;     // ָ����ָ����һ���ڵ�
} LNode, * LinkList;        // ����ڵ����ͺͽڵ�ָ������

// ��ʼ��������ͷָ����Ϊ��
void InitLinkList(LinkList* head) {
	*head = NULL;
}
//�ƶ�ָ����i-1���ڵ�
LNode* MovePoint(LinkList* L, int i)
{
	if (i < 1)
	{
		printf("λ�ô���");
		return NULL;
	}
	int j = 0;
	LNode* p = *L;
	while (p != NULL && j < i - 1)
	{
		p = p->next;
		j++;
	}
	if (p == NULL)
	{
		printf("ǰ���ڵ㲻����\n");
		return NULL;
	}
	return p;
}
//��ָ��λ��i��ǰ�����ڵ�
int FrontInsert(LinkList* L, int i, ElemType e)
{
	LNode* p = MovePoint(L, i);
	if (p == NULL)
	{
		return 0;
	}
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)
	{
		perror("FrontInsert:");
		printf("�����ڴ�ʧ��\n");
		return 0;
	}
	ElemType temp = p->data;
	p->data = e;
	s->data = temp;
	s->next = p->next;
	p->next = s;
	return 1;
}
// ������ĵ� i ��λ�ò���Ԫ�� e
int InsertList(LinkList* L, int i, ElemType e) {
	if (i < 1) {
		return 0; // ����λ�÷Ƿ�
	}
	LinkList p = *L; // p ָ��ͷ�ڵ�
	int j = 0;
	while (p != NULL && j < i - 1) {
		p = p->next; // �ҵ��� i-1 ���ڵ�
		j++;
	}
	if (p == NULL) {
		return 0; // ����λ�ò�����
	}
	// �����½ڵ�
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL) {
		return 0; // �ڴ����ʧ��
	}
	s->data = e;
	s->next = p->next; // ���½ڵ�� next ָ��ָ��� i ���ڵ�
	p->next = s; // ���� i-1 ���ڵ�� next ָ��ָ���½ڵ�
	return 1; // ����ɹ�
}
void deleteLNode(LinkList* L, ElemType e)
{
	LNode* p = *L;
	LNode* pre = *L;
	int i = 0;
	while (p)
	{
		if (p->data == e)
		{
			pre->next = p->next;
			free(p);
			p = NULL;
			break;
		}
		pre = p;
		p = p->next;
		i++;
	}
}
void reverseLinlist1(LinkList* L, int size)
{
	int x = size;
	int s = size / 2;
	if (L == NULL)
	{
		return;
	}
	LNode* front = *L;
	LNode* rear = MovePoint(L, x);
	ElemType e;
	while (s)
	{
		e = front->data;
		front->data = rear->data;
		rear->data = e;
		x--;
		rear = MovePoint(L, x);
		front = front->next;
		s--;
	}
}
void reverseLinklist2(LinkList* L)
{
	if (*L == NULL)
	{
		return;
	}
	LNode* head = *L;
	LNode* p = *L;
	LNode* r = NULL;
	while (p)
	{
		if (r == NULL)
		{
			r = p->next;
			p->next = NULL;
			p = r;
		}
		r = p->next;
		p->next = head;
		head = p;
		p = r;
	}
	*L = head;
}
void My_print(LinkList L)
{
	LNode* p = L;
	while (p)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
void insertLNodeOrder(LinkList* L, LNode* x)
{
	if (*L == NULL)
	{
		return;
	}
	LNode* p = *L;
	LNode* pre = NULL;
	while (p&&x->data > p->data)
	{
		pre = p;
		p = p->next;
	}
	if (pre == NULL)
	{
		x->next = p;
		*L = x;
	}
	else
	{
		x->next = pre->next;
		pre->next = x;
	}
}
void Linksort(LinkList* L)
{
	if (*L == NULL)
	{
		return;
	}
	LNode* head = *L;
	LNode* pre = *L;
	LNode* p = head->next;
	while (p)
	{
		if (head->data > p->data)
		{
			pre = head;
			head = p;
		}
		p = p->next;
		if (p == NULL)
		{
			pre->next = head->next;
			head->next = NULL;
		}
	}
	p = *L;
	pre = p;
	while (p)
	{
		while (p)
		{
			if (pre->data < p->data)
			{
				pre = p;
			}
			p = p->next;
		}
		if (pre == *L)
		{
			*L = pre->next;
		}
		pre->next = head->next;
		head->next = pre;
		p = *L;
		pre = *L;
	}

	*L = head;
}
int main() {

	LinkList L;             // ��������ͷָ��
	InitLinkList(&L);       // ��ʼ������
	LNode head = { 10,NULL };
	LNode x = { 50,NULL };
	L = &head;
	FrontInsert(&L, 1, 20);
	FrontInsert(&L, 1, 30);
	FrontInsert(&L, 1, 40);
	My_print(L);
	reverseLinlist1(&L, 4);//���ñ���Ԫ��
	My_print(L);
	reverseLinklist2(&L);//��������
	My_print(L);
	Linksort(&L);
	insertLNodeOrder(&L,&x);
	My_print(L);
	return 0;
}
