#include<stdio.h> // ������׼���������

#define MAXSIZE 100 // �������ڵ���������
#define CAPACITY 10 // ����ջ���������

typedef int Elemtype; // �������ڵ��ջ��Ԫ�ص�����Ϊ����
typedef struct stack // ����ջ�Ľṹ��
{
    Elemtype data[CAPACITY]; // ��������
    int top; // ջ��ָ��
}SQLstack;

typedef struct // �������ڵ�Ľṹ��
{
    Elemtype data; // ����
    int isempity; // �Ƿ�Ϊ��
}TreeNode[MAXSIZE];

void IniStack(SQLstack* s) // ��ʼ��ջ
{
    s->top = -1; // ջ��ָ����Ϊ-1����ʾջΪ��
}

int Puch(SQLstack* s, Elemtype e) // Ԫ����ջ
{
    if (s->top == CAPACITY - 1) // ���ջ����
    {
        printf("ջ������\n");
        return 0; // ��ջʧ��
    }
    s->data[++(s->top)] = e; // ջ��ָ���1��Ԫ����ջ
    return 1; // ��ջ�ɹ�
}

Elemtype Pop(SQLstack* s) // Ԫ�س�ջ
{
    if (s->top == -1) // ���ջΪ��
    {
        printf("��ջ\n");
        return 0; // ��ջʧ��
    }
    Elemtype e = s->data[s->top--]; // ��ȡջ��Ԫ�أ�ջ��ָ���1
    return e; // ���س�ջ��Ԫ��
}

Elemtype Getelement(SQLstack* s) // ��ȡջ��Ԫ��
{
    if (s->top == -1) // ���ջΪ��
    {
        printf("��ջ\n");
        return 0; // ����0
    }
    return s->data[s->top]; // ����ջ��Ԫ��
}

void IniTree(TreeNode T)  // ��ʼ��������
{
    if (T == NULL) // ���������Ϊ��
    {
        return; // ����
    }
    for (int i = 0; i < MAXSIZE; i++) // �����������ڵ�����
    {
        T[i].isempity = 1; // ���ڵ��isempity��Ϊ1����ʾΪ��
    }
}

int addElem(TreeNode T, Elemtype e) // ���Ԫ�ص���������
{
    for (int i = 1; i < MAXSIZE; i++) // �����������ڵ�����
    {
        if (T[i].isempity) // �����ǰ�ڵ�Ϊ��
        {
            T[i].data = e; // ������e��ӵ���ǰ�ڵ�
            T[i].isempity = 0; // ����ǰ�ڵ��isempity��Ϊ0����ʾ�ǿ�
            break; // ����ѭ��
        }
    }
    return 1; // ��ӳɹ�
}

int preorderVist(TreeNode T, SQLstack* S) // ��������ǰ�����
{
    Elemtype TLNode = 1; // �������ڵ�
    Puch(S, T[1].data); // ���ڵ���ջ
    while (T[TLNode].isempity != 1) // ѭ��ֱ����������
    {
        TLNode = Pop(S); // ���������ĸ�������������ҽڵ�ķ���
        if (TLNode < 1) // ���ջ��Ԫ��С��1
        {
            return 1; // ��������
        }
        printf("%d", TLNode); // �����������ڵ�

        if (T[2 * TLNode + 1].isempity == 0) // ������ӽڵ㲻Ϊ��
        {
            Puch(S, T[2 * TLNode + 1].data); // ���ӽڵ���ջ
        }
        if (T[2 * TLNode].isempity == 0) // ������ӽڵ㲻Ϊ��
        {
            Puch(S, T[2 * TLNode].data); // ���ӽڵ���ջ
        }
    }
    return 1; // �������
}

int main() // ������
{
    TreeNode T; // �����������ڵ�����
    SQLstack S; // ����ջ
    IniStack(&S); // ��ʼ��ջ
    addElem(T, 1); // ������������Ԫ��
    addElem(T, 2);
    addElem(T, 3);
    addElem(T, 4);
    addElem(T, 5);
    addElem(T, 6);
    preorderVist(T, &S); // ����ǰ�����
    return 0; // ����0����ʾ������������
}
