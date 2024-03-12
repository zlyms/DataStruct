#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#pragma warning(disable:4996)

// 定义链表节点的数据类型为整数
typedef int Elemtype;

// 定义链表节点结构体
typedef struct LNode
{
	struct LNode* next; // 指向下一个节点的指针
	Elemtype data; // 存储节点数据的变量
} LNode, * LinkList;

// 初始化链表，参数为指向链表头节点的指针的指针
void IniLinkList(LinkList* L)
{
	// 分配内存给链表头节点
	*L = (LNode*)malloc(sizeof(LNode));
	if (*L == NULL)
	{
		// 内存申请失败的错误处理
		printf("内存申请失败\n");
		perror("IniLinkList:");
		return;
	}
	(*L)->next = NULL; // 将链表头节点的下一个节点指针置为空
}

// 向链表中添加元素
int addElem(LinkList L, Elemtype e)
{
	// 分配内存给新节点
	LNode* p = (LNode*)malloc(sizeof(LNode));
	if (p == NULL)
	{
		// 内存申请失败的错误处理
		printf("内存申请失败\n");
		perror("addElem:");
		return 0;
	}
	p->data = e; // 将新节点的数据域设置为传入的数据 e
	p->next = NULL; // 将新节点的下一个节点指针置为空

	LNode* temp = L;
	// 找到链表的尾部节点
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = p; // 将新节点连接到链表尾部

	return 1;
}
int createPublicLNode(LinkList A, LinkList B, LinkList C)
{
	// 检查链表 A 和链表 B 是否为空
	if (A->next == NULL || B->next == NULL)
	{
		return 0; // 如果任何一个链表为空，则无法找到公共节点，返回 0
	}

	LNode* rear, * p1, * p2; // 定义指针 rear, p1, p2
	p1 = A->next; // p1 指向链表 A 的第一个节点
	p2 = B->next; // p2 指向链表 B 的第一个节点
	rear = C; // rear 指向链表 C 最后一个节点

	// A B表不为空时，继续执行循环
	while (p1 != NULL && p2 != NULL)
	{
		// 如果 p1 和 p2 指向的节点数据相同
		if (p1->data == p2->data)
		{
			// 创建一个新的节点并赋值为 p1 的数据
			LNode* ptr = (LNode*)malloc(sizeof(LNode));
			if (ptr == NULL)
			{
				printf("空间申请失败\n");
				perror("createPublicLNode:");
				return 0; // 如果内存分配失败，则返回 0
			}
			ptr->data = p1->data;

			// 将新节点连接到链表 C 的尾部
			rear->next = ptr;
			rear = ptr;

			// 移动 p1 和 p2 到下一个节点
			p1 = p1->next;
			p2 = p2->next;
		}
		//让数小的先走，避免重复比较
		else if (p1->data - p2->data < 0)
		{
			p1 = p1->next; // 移动 p1 到下一个节点
		}
		else
		{
			p2 = p2->next; // 移动 p2 到下一个节点
		}
	}
	return 1; // 函数执行成功，返回 1
}

int main()
{
	LinkList L1;
	LinkList L2;
	LinkList L3;
	IniLinkList(&L1); // 初始化链表
	IniLinkList(&L2); // 初始化链表
	IniLinkList(&L3); // 初始化链表
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
