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

// 删除链表中重复的元素
int removeExcessElem(LinkList L)
{
	LNode* p = L->next->next; // p 指向链表的第二个节点
	LNode* q = L->next; // q 指向链表的第一个节点
	if (p == NULL)
	{
		// 链表中没有节点或只有一个节点，无需处理
		return 0;
	}
	while (p != NULL)
	{
		if (p->data == q->data)
		{
			// 如果当前节点的数据与前一个节点的数据相同，则删除当前节点
			q->next = p->next;
			free(p); // 释放当前节点的内存
			p = NULL;
			p = q->next; // 移动 p 到下一个节点
		}
		else
		{
			// 如果当前节点的数据与前一个节点的数据不同，则继续遍历链表
			q = q->next;
			p = p->next;
		}
	}
	return 1;
}

int main()
{
	LinkList L1;
	IniLinkList(&L1); // 初始化链表

	// 向链表中添加元素
	addElem(L1, 1);
	addElem(L1, 2);
	addElem(L1, 2);
	addElem(L1, 3);
	addElem(L1, 3);
	addElem(L1, 3);

	// 删除链表中重复的元素
	removeExcessElem(L1);

	return 0;
}
