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
    *head = (LinkList)malloc(sizeof(LNode));
    if (*head == NULL) 
    {
        perror("InitLinkList:");
        printf("����ռ�ʧ��\n");
        return ;
    }
    (*head)->data = 0;
    (*head)->next = (*head);
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
    printf("ǰ��ɹ�\n");
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
//ɾ����i��λ�õ�ǰһ���ڵ�
int FrontDelete(LinkList* L, int i, ElemType* e)
{
    LNode* p = MovePoint(L, i);
    if (p == NULL)
    {
        return 0;
    }
    LNode* s = p->next;
    ElemType temp = p->data;
    p->data = (p->next)->data;
    p->next = s->next;
    *e = temp;
    free(s);
    s = NULL;

    return *e;//����ɾ��Ԫ��
}
//��ɾ��ɾ����i-1��λ�õĺ�һ���ڵ�Ҳ����i
int DeleteList(LinkList* L, int i, ElemType* e)
{
    if (i < 1) {
        return 0; // ����λ�÷Ƿ�
    }
    LinkList p = *L; // p ָ��ͷ�ڵ�
    int j = 0;
    while (p != NULL && j < i - 1) {
        p = p->next; // �ҵ��� i-1 ���ڵ�
        j++;
    }
    if (p == NULL) //ָ��λ��ǰ���ڵ㲻����
    {
        printf("ָ���ڵ㲻����\n");
        return 0;
    }
    if (p->next == NULL)//ָ��λ���޽ڵ�
    {
        printf("ָ���ڵ㲻����\n");
        return 0;
    }
    LNode* s = p->next;
    *e = (p->next)->data;
    p->next = (p->next)->next;
    free(s);
    printf("ɾ���ɹ�\n");
    return *e;//����ɾ��Ԫ��
}
int getValue(LinkList* L, ElemType e)
{
    LNode* p = (*L)->next;
    int i = 1;
    int flase = 0;
    while (p != NULL)
    {
        if (p->data != e)
        {
            p = p->next;

        }
        else
        {
            printf("��%d��Ԫ�ص�ֵ�ǣ�%d\n", i, e);
            flase++;
            p = p->next;
        }
        i++;
    }
    if (!flase)
    {
        printf("û���ҵ�");
        return 0;
    }
    return 1;
}

// ��ȡ�����е� i ��λ�õ�Ԫ��ֵ
int GetElem(LinkList L, int i, ElemType* e) {
    if (i < 1) {
        return 0; // λ�÷Ƿ�
    }
    LinkList p = L;
    int j = 0;
    while (p != NULL && j < i) {
        p = p->next; // ���������ҵ��� i ���ڵ�
        j++;
    }
    if (p == NULL) {
        return 0; // �� i ��Ԫ�ز�����
    }
    *e = p->data; // ��ȡ�� i ��Ԫ�ص�ֵ
    return 1; // ��ȡ�ɹ�
}

int main() {

    LinkList L;             // ��������ͷָ��
    InitLinkList(&L);       // ��ʼ������
    InsertList(&L, 1, 10); // �ڵ�һ��λ�ò���Ԫ�� 10
    InsertList(&L, 1, 20);


    // ��ȡ�����е�һ��Ԫ�ص�ֵ�����
    ElemType elem;
    // FrontDelete(&L, 2, &elem);
  /*   if (GetElem(L, 1, &elem)) {
         printf("��һ��Ԫ�ص�ֵ�ǣ�%d\n", elem);
     }
     else {
         printf("��ȡԪ��ʧ��\n");
     }*/
    LinkList p = L;
    while (p != NULL) 
    {
        printf("%d\n", p->data);
        p = p->next;
    }

    return 0;
}
