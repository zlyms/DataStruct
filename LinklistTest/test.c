#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

// 定义链表节点结构体
typedef struct LNode {
	ElemType data;          // 数据域
	struct LNode* next;     // 指针域，指向下一个节点
} LNode, * LinkList;        // 定义节点类型和节点指针类型

// 初始化链表，将头指针置为空
void InitLinkList(LinkList* head) {
	*head = NULL;
}
//移动指针至i-1个节点
LNode* MovePoint(LinkList* L, int i)
{
	if (i < 1)
	{
		printf("位置错误");
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
		printf("前驱节点不存在\n");
		return NULL;
	}
	return p;
}
//在指定位置i的前面插入节点
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
		printf("申请内存失败\n");
		return 0;
	}
	ElemType temp = p->data;
	p->data = e;
	s->data = temp;
	s->next = p->next;
	p->next = s;
	return 1;
}
// 在链表的第 i 个位置插入元素 e
int InsertList(LinkList* L, int i, ElemType e) {
	if (i < 1) {
		return 0; // 插入位置非法
	}
	LinkList p = *L; // p 指向头节点
	int j = 0;
	while (p != NULL && j < i - 1) {
		p = p->next; // 找到第 i-1 个节点
		j++;
	}
	if (p == NULL) {
		return 0; // 插入位置不存在
	}
	// 创建新节点
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL) {
		return 0; // 内存分配失败
	}
	s->data = e;
	s->next = p->next; // 将新节点的 next 指针指向第 i 个节点
	p->next = s; // 将第 i-1 个节点的 next 指针指向新节点
	return 1; // 插入成功
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

	LinkList L;             // 声明链表头指针
	InitLinkList(&L);       // 初始化链表
	LNode head = { 10,NULL };
	LNode x = { 50,NULL };
	L = &head;
	FrontInsert(&L, 1, 20);
	FrontInsert(&L, 1, 30);
	FrontInsert(&L, 1, 40);
	My_print(L);
	reverseLinlist1(&L, 4);//逆置表中元素
	My_print(L);
	reverseLinklist2(&L);//逆置链表
	My_print(L);
	Linksort(&L);
	insertLNodeOrder(&L,&x);
	My_print(L);
	return 0;
}
