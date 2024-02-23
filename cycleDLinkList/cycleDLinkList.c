#include<stdio.h>
#include<stdlib.h>

typedef int Elemtype;

// ����˫������ṹ��
typedef struct DLNode {
	struct DLNode* prior; // ָ��ǰһ������ָ��
	Elemtype data; // ������
	struct DLNode* next; // ָ���һ������ָ��
} DLNode, * DLinkList;

// ��ʼ��˫����
int IniDLinkList(DLinkList* L) {
	DLNode* p = *L; // ͷָ��
	if (p == NULL) {
		return 0;
	}
	p = (DLNode*)malloc(sizeof(DLNode)); // �������ڴ�ռ�
	if (p == NULL) {
		perror("IniLinkLIst:");
		printf("�ռ�����ʧ��");
		return 0;
	}
	p->next = p;
	p->data = 0;
	p->prior = p;
	*L = p; // ����ͷָ��
	return 1;
}

// �ƶ�ָ�뵽�� i ������λ��
DLNode* MovePoint(DLinkList L, int i) {
	if (i < 1) {
		printf("λ�ô���\n");
		return NULL;
	}
	int j = 0;
	DLNode* p = L; // ͷָ��
	while (p != NULL && j < i - 1) {
		p = p->next; // �ƶ�ָ��
		j++;
	}
	if (p == NULL) {
		printf("λ�ô���\n");
		return NULL;
	}
	return p;
}

// �ڵ� i ��λ�ò���Ԫ�� e
int DLinkListInser(DLinkList L, int i, Elemtype e) {
	DLNode* p = MovePoint(L, i); // �ҵ��� i ������λ��
	if (p == NULL) {
		return 0;
	}
	DLNode* s = (DLNode*)malloc(sizeof(DLNode)); // �����½��
	if (s == NULL) {
		perror("DLinkListInser:");
		printf("�ռ�����ʧ��\n");
		return 0;
	}
	s->data = e; // �����½�������

	(p->next)->prior = s; // ���º�һ������ǰ��ָ��
	s->next = p->next; // �½��ָ��ԭ���� i ��λ�õĽ��
	p->next = s; // ǰһ�����ָ���½��
	s->prior = p; // �½���ǰ��ָ��ǰһ�����
	return 0;
}

// ɾ���� i �����
int DeleteDLNode(DLinkList L, int i) {
	DLNode* p = MovePoint(L, i); // �ҵ��� i ������λ��
	if (p == NULL) {
		return 0;
	}
	DLNode* q = p->next; // ��ɾ���Ľ��
	if (q == NULL) {
		return 0;
	}
	if (q->next == NULL) { // �����ɾ���Ľ�������һ�����
		free(q);
		p->next = NULL;
		return 1;
	}
	q->next->prior = p; // ���º�һ������ǰ��ָ��
	p->next = q->next; // ǰһ�����ָ���һ�����
	free(q); // �ͷŴ�ɾ�������ڴ�ռ�
	q = NULL;
	return 1;
}

// ��ȡ�� i �����
DLNode* GetElem(DLinkList L, int i) {
	if (i < 1) {
		printf("����λ�ô���\n");
		return NULL;
	}
	DLNode* p = MovePoint(L, i); // �ҵ��� i-1 ������λ��
	if (p == NULL) {
		printf("����λ�ô���\n");
		return NULL;
	}
	DLNode* q = p->next; // ��ȡ�� i �����
	if (q == NULL) {
		printf("����λ�ô���\n");
		return NULL;
	}
	return q;
}

int main() {
	DLinkList L;
	IniDLinkList(&L); // ��ʼ��˫����
	DLinkListInser(L, 1, 10); // �ڵ�һ��λ�ò���Ԫ�� 10
	DLinkListInser(L, 2, 20); // �ڵڶ���λ�ò���Ԫ�� 20
	DLinkListInser(L, 3, 30); // �ڵ�����λ�ò���Ԫ�� 30
	DLinkListInser(L, 4, 40); // �ڵ��ĸ�λ�ò���Ԫ�� 40
	DeleteDLNode(L, 4); // ɾ�����ĸ�λ�õĽ��
	DLinkList p = L->next; // ͷ�ڵ����һ�����
	//while (p != NULL) { // ˳�����
	//	printf("%d\n", p->data);
	//	p = p->next;
	//}
	//printf("-----------------------------------------\n");
	p = GetElem(L, 3); // ��ȡ������λ�õĽ��
	while (p != NULL ) { // �������
		printf("%d\n", p->data);
		p = p->next;
	}
	return 0;
}
