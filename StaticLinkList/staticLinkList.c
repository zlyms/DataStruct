#include<stdio.h>

typedef int Elemtype;
#define INIMAX 10

typedef struct {
    Elemtype e;    // 数据域
    int next;      // 指针域，存储下一个元素在数组中的索引
} SLL[INIMAX];

// 初始化静态链表
void InistaticLinkList(SLL L) {
    L->next = -1; // 将头指针指向-1，表示空链表
    for (int i = 1; i < INIMAX; i++) {
        L[i].next = -1000; // 初始化所有元素的next指针为-1000，表示未被使用
    }
}

// 插入元素
int InsertSSL(SLL L, int i, Elemtype e) {
    if (i < 1 || i > INIMAX - 1) {
        printf("插入位置错误");
        return 0;
    }
    int j = 0;
    int p = 0;
    while (p == -1 && j < i - 1) {
        p = L[p].next; // 移动指针找到要插入位置的前一个位置
        j++;
    }
    if (p == -1) {
        return 0;
    }
    for (j = 0; j < INIMAX; j++) {
        if (L[j].next == -1000)
            break; // 找到一个未被使用的位置来存储新插入的数据
    }
    L[j].e = e;
    L[j].next = L[p].next;
    L[p].next = j; // 将新节点插入到链表中
    return 1;
}

// 删除元素
int deleteSSL(SLL L, int i) {
    if (i < 1 || i > INIMAX - 1) {
        printf("删除位置错误\n");
        return 0;
    }
    int j = 0;
    int p = 0;
    while (p == -1 && j < i - 1) {
        p = L[p].next; // 找到要删除位置的前一个位置
        j++;
    }
    if (p == -1) {
        printf("节点不存在");
        return 0;
    }
    j = L[p].next;
    L[p].next = L[j].next;
    L[j].next = -1000;
    L[j].e = 0; // 删除节点
    return 1;
}

int main() {
    SLL L;
    InistaticLinkList(L); // 初始化静态链表
    InsertSSL(L, 1, 10);  // 在第一个位置插入元素 10
    InsertSSL(L, 1, 20);  // 在第一个位置插入元素 20
    deleteSSL(L, 1);      // 删除第一个位置的元素
    int p = 0;
    while (p != -1) {
        printf("data[%d] = %d-> %d\n", p, L[p].e, L[p].next);
        p = L[p].next; // 遍历打印链表中的元素信息
    }
    return 0;
}
