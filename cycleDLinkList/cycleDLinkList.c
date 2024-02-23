#include<stdio.h>
#include<stdlib.h>

typedef int Elemtype;

// 定义双链表结点结构体
typedef struct DLNode {
	struct DLNode* prior; // 指向前一个结点的指针
	Elemtype data; // 数据域
	struct DLNode* next; // 指向后一个结点的指针
} DLNode, * DLinkList;

// 初始化双链表
int IniDLinkList(DLinkList* L) {
	DLNode* p = *L; // 头指针
	if (p == NULL) {
		return 0;
	}
	p = (DLNode*)malloc(sizeof(DLNode)); // 分配结点内存空间
	if (p == NULL) {
		perror("IniLinkLIst:");
		printf("空间申请失败");
		return 0;
	}
	p->next = p;
	p->data = 0;
	p->prior = p;
	*L = p; // 更新头指针
	return 1;
}

// 移动指针到第 i 个结点的位置
DLNode* MovePoint(DLinkList L, int i) {
	if (i < 1) {
		printf("位置错误\n");
		return NULL;
	}
	int j = 0;
	DLNode* p = L; // 头指针
	while (p != NULL && j < i - 1) {
		p = p->next; // 移动指针
		j++;
	}
	if (p == NULL) {
		printf("位置错误\n");
		return NULL;
	}
	return p;
}

// 在第 i 个位置插入元素 e
int DLinkListInser(DLinkList L, int i, Elemtype e) {
	DLNode* p = MovePoint(L, i); // 找到第 i 个结点的位置
	if (p == NULL) {
		return 0;
	}
	DLNode* s = (DLNode*)malloc(sizeof(DLNode)); // 创建新结点
	if (s == NULL) {
		perror("DLinkListInser:");
		printf("空间申请失败\n");
		return 0;
	}
	s->data = e; // 设置新结点的数据

	(p->next)->prior = s; // 更新后一个结点的前驱指针
	s->next = p->next; // 新结点指向原来第 i 个位置的结点
	p->next = s; // 前一个结点指向新结点
	s->prior = p; // 新结点的前驱指向前一个结点
	return 0;
}

// 删除第 i 个结点
int DeleteDLNode(DLinkList L, int i) {
	DLNode* p = MovePoint(L, i); // 找到第 i 个结点的位置
	if (p == NULL) {
		return 0;
	}
	DLNode* q = p->next; // 待删除的结点
	if (q == NULL) {
		return 0;
	}
	if (q->next == NULL) { // 如果待删除的结点是最后一个结点
		free(q);
		p->next = NULL;
		return 1;
	}
	q->next->prior = p; // 更新后一个结点的前驱指针
	p->next = q->next; // 前一个结点指向后一个结点
	free(q); // 释放待删除结点的内存空间
	q = NULL;
	return 1;
}

// 获取第 i 个结点
DLNode* GetElem(DLinkList L, int i) {
	if (i < 1) {
		printf("查找位置错误\n");
		return NULL;
	}
	DLNode* p = MovePoint(L, i); // 找到第 i-1 个结点的位置
	if (p == NULL) {
		printf("查找位置错误\n");
		return NULL;
	}
	DLNode* q = p->next; // 获取第 i 个结点
	if (q == NULL) {
		printf("查找位置错误\n");
		return NULL;
	}
	return q;
}

int main() {
	DLinkList L;
	IniDLinkList(&L); // 初始化双链表
	DLinkListInser(L, 1, 10); // 在第一个位置插入元素 10
	DLinkListInser(L, 2, 20); // 在第二个位置插入元素 20
	DLinkListInser(L, 3, 30); // 在第三个位置插入元素 30
	DLinkListInser(L, 4, 40); // 在第四个位置插入元素 40
	DeleteDLNode(L, 4); // 删除第四个位置的结点
	DLinkList p = L->next; // 头节点的下一个结点
	//while (p != NULL) { // 顺序遍历
	//	printf("%d\n", p->data);
	//	p = p->next;
	//}
	//printf("-----------------------------------------\n");
	p = GetElem(L, 3); // 获取第三个位置的结点
	while (p != NULL ) { // 逆序遍历
		printf("%d\n", p->data);
		p = p->next;
	}
	return 0;
}
