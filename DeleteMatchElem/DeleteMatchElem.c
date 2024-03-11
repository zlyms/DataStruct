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
int Addelem(LinkList* L,ElemType e)
{
    LNode* s = (LNode*)malloc(sizeof(LNode));
    if (s == NULL) 
    {
        perror("AddElem:");
        printf("�ռ�����ʧ��\n");
        return 0;
    }
    LNode* p=*L;
    s->data = e;
    if (*L == NULL) 
    {
        s->next = *L;
        *L = s;
        p = *L;
    }
    else 
    {
        while (p->next != NULL) 
        {
            p = p->next;
        }
        s->next = p->next;
        p->next = s;

    }
    return 1;
}
int DeleMatchElem(ElemType i,ElemType j, LinkList*L)
{
    if (*L == NULL) 
    {
        printf("�ձ�\n");
        return 0;
    }
    LNode* pre = *L;
    LNode* p = *L;
    while (p!=NULL)
    {
        if (p==*L&&p->data<j && p->data>i)
        {
            *L = (*L)->next;
            free(p);
            p = *L;
        }

        if (p->data<j && p->data>i)
        {
                pre->next = p->next;
                free(p);
                p = pre->next;
        }
        else 
        {
            pre = p;
            p = p->next;
        }
    }
    return 1;
}
int main() {

    LinkList L;             // ��������ͷָ��
    int i = 1;
    InitLinkList(&L);       // ��ʼ������
    Addelem(&L, 1);
    Addelem(&L, 2);
    Addelem(&L, 3);
    Addelem(&L, 4);
    Addelem(&L, 5);
    DeleMatchElem(0,2,&L);
    return 0;
}
