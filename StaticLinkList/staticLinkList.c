#include<stdio.h>

typedef int Elemtype;
#define INIMAX 10

typedef struct {
    Elemtype e;    // ������
    int next;      // ָ���򣬴洢��һ��Ԫ���������е�����
} SLL[INIMAX];

// ��ʼ����̬����
void InistaticLinkList(SLL L) {
    L->next = -1; // ��ͷָ��ָ��-1����ʾ������
    for (int i = 1; i < INIMAX; i++) {
        L[i].next = -1000; // ��ʼ������Ԫ�ص�nextָ��Ϊ-1000����ʾδ��ʹ��
    }
}

// ����Ԫ��
int InsertSSL(SLL L, int i, Elemtype e) {
    if (i < 1 || i > INIMAX - 1) {
        printf("����λ�ô���");
        return 0;
    }
    int j = 0;
    int p = 0;
    while (p == -1 && j < i - 1) {
        p = L[p].next; // �ƶ�ָ���ҵ�Ҫ����λ�õ�ǰһ��λ��
        j++;
    }
    if (p == -1) {
        return 0;
    }
    for (j = 0; j < INIMAX; j++) {
        if (L[j].next == -1000)
            break; // �ҵ�һ��δ��ʹ�õ�λ�����洢�²��������
    }
    L[j].e = e;
    L[j].next = L[p].next;
    L[p].next = j; // ���½ڵ���뵽������
    return 1;
}

// ɾ��Ԫ��
int deleteSSL(SLL L, int i) {
    if (i < 1 || i > INIMAX - 1) {
        printf("ɾ��λ�ô���\n");
        return 0;
    }
    int j = 0;
    int p = 0;
    while (p == -1 && j < i - 1) {
        p = L[p].next; // �ҵ�Ҫɾ��λ�õ�ǰһ��λ��
        j++;
    }
    if (p == -1) {
        printf("�ڵ㲻����");
        return 0;
    }
    j = L[p].next;
    L[p].next = L[j].next;
    L[j].next = -1000;
    L[j].e = 0; // ɾ���ڵ�
    return 1;
}

int main() {
    SLL L;
    InistaticLinkList(L); // ��ʼ����̬����
    InsertSSL(L, 1, 10);  // �ڵ�һ��λ�ò���Ԫ�� 10
    InsertSSL(L, 1, 20);  // �ڵ�һ��λ�ò���Ԫ�� 20
    deleteSSL(L, 1);      // ɾ����һ��λ�õ�Ԫ��
    int p = 0;
    while (p != -1) {
        printf("data[%d] = %d-> %d\n", p, L[p].e, L[p].next);
        p = L[p].next; // ������ӡ�����е�Ԫ����Ϣ
    }
    return 0;
}
