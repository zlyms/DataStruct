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
    *head = (LinkList)malloc(sizeof(LNode));
    if (*head == NULL) 
    {
        perror("InitLinkList:");
        printf("申请空间失败\n");
        return ;
    }
    (*head)->data = 0;
    (*head)->next = (*head);
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
    printf("前插成功\n");
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
//删除第i个位置的前一个节点
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

    return *e;//返回删除元素
}
//后删，删除第i-1个位置的后一个节点也就是i
int DeleteList(LinkList* L, int i, ElemType* e)
{
    if (i < 1) {
        return 0; // 插入位置非法
    }
    LinkList p = *L; // p 指向头节点
    int j = 0;
    while (p != NULL && j < i - 1) {
        p = p->next; // 找到第 i-1 个节点
        j++;
    }
    if (p == NULL) //指定位置前驱节点不存在
    {
        printf("指定节点不存在\n");
        return 0;
    }
    if (p->next == NULL)//指定位置无节点
    {
        printf("指定节点不存在\n");
        return 0;
    }
    LNode* s = p->next;
    *e = (p->next)->data;
    p->next = (p->next)->next;
    free(s);
    printf("删除成功\n");
    return *e;//返回删除元素
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
            printf("在%d个元素的值是：%d\n", i, e);
            flase++;
            p = p->next;
        }
        i++;
    }
    if (!flase)
    {
        printf("没有找到");
        return 0;
    }
    return 1;
}

// 获取链表中第 i 个位置的元素值
int GetElem(LinkList L, int i, ElemType* e) {
    if (i < 1) {
        return 0; // 位置非法
    }
    LinkList p = L;
    int j = 0;
    while (p != NULL && j < i) {
        p = p->next; // 遍历链表找到第 i 个节点
        j++;
    }
    if (p == NULL) {
        return 0; // 第 i 个元素不存在
    }
    *e = p->data; // 获取第 i 个元素的值
    return 1; // 获取成功
}

int main() {

    LinkList L;             // 声明链表头指针
    InitLinkList(&L);       // 初始化链表
    InsertList(&L, 1, 10); // 在第一个位置插入元素 10
    InsertList(&L, 1, 20);


    // 获取链表中第一个元素的值并输出
    ElemType elem;
    // FrontDelete(&L, 2, &elem);
  /*   if (GetElem(L, 1, &elem)) {
         printf("第一个元素的值是：%d\n", elem);
     }
     else {
         printf("获取元素失败\n");
     }*/
    LinkList p = L;
    while (p != NULL) 
    {
        printf("%d\n", p->data);
        p = p->next;
    }

    return 0;
}
